#include "ops.h"
#include "interpreter.h"
#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum regs {
    A = 1,
    B,
    C,
    D,
    SP,
    BP
};

static int tok_start = BP;
static char *tokens[RAM_SZ];
static int tok_cnt = BP;

static int lbl_off = 0;


// LABEL RELATED FUNCTIONS ================================================
// print out the labels in an executable.
void increment_labels(executable_t *exec, int len, int inc) {
    
    lnode_t *cur = exec->labels;
    while (cur) {
        if (cur->address >= len) {
            cur->address += inc;
        }

        cur = cur->next;
    }

}

// traverses the label linked list to determine if a word in the asm
// is a label. if it is, the corresponding address is returned, otherwise 0
int is_label(char *word, executable_t *exec) {
    lnode_t *current = exec->labels;

    while (current) {
        if (strcmp(current->name, word) == 0) {
            return current->address; 
        }

        current = current->next;
    }

    return 0;
}

// this function adds a new lbl to the executable mapped to the provided address
void add_label(executable_t *exec, char *name, int addr) {
    lnode_t *lbl = malloc(sizeof(lnode_t));

    char *lbl_name = strdup((++name));
    lbl->name = lbl_name;
    lbl->address = addr + lbl_off;

    lnode_t *current = exec->labels;

    if (!current) {
        exec->labels = lbl;
        return; 
    }
    else {
        while (current->next) {
            current = current->next; 
        }
        
        current->next = lbl;
    }
}
// ========================================================================


// COMPILATION FUNCTIONS ==================================================

// goes through a single line and saves tokens delimited by whitespace
// the tokens are stored in a static array of strings saved on the heap
int tokenize(executable_t *exec, char *line) {
    int in_word = 0;
    char *start;

    while (*line != '\0' && *line != '~') {
        if (!in_word) {
            if (!(isspace(*line))) {
                start = line;
                in_word = 1;
            }
        }
        else {
            if (isspace(*line)) {
                *line = '\0';
                
                if (*start == '$') 
                    add_label(exec, start, tok_cnt + 1);   
                else {
                    if (*start == '*') 
                        lbl_off += 2;

                    tokens[tok_cnt++] = strdup(start); 
                }

                in_word = 0;
            }
        }

        line++;
    }
    
    return 0;
}

void add_dereference(executable_t *exec, char *oper) {
    char *dref = strdup("DREF");
    
    ++oper;

    exec->code[exec->length++] = get_opcode(dref);
    exec->code[exec->length++] = is_label(oper, exec);

    free(dref);
}

// goes through the array of tokens, converts them to op code and places
// them in the executable structure
void process_inst(executable_t *exec, op_t *op, int *index) {
    int i = 0;

    int opcode;
    int i_code;

    char *operand;

    for (i = 0; i < op->argc; i++) {
        operand = tokens[(*index) + i];

        if (operand[0] == '*') 
            add_dereference(exec, operand);
    }

    for (i = 0; i < op->argc; i++) {
        operand = tokens[(*index)++];

        int lbl = is_label(operand, exec);
        
        if (operand[0] == '*') {
            i_code |= R << (i * 4);
            opcode = D;
        }

        else if (operand[0] == '&') {
            i_code |= L << (i * 4);
            opcode = is_label(operand + 1, exec);
        }

        else if (lbl) {
            i_code |= M << (i * 4);
            opcode = lbl;
        }

        else {
            i_code |= L << (i * 4);
            opcode = atoi(operand);
        }


        printf("STR: %s -> OP: %d     ADDR: %d \n", operand, opcode, exec->length + i + 1);
        exec->code[exec->length + i + 1] = opcode;
        free(operand);
    }


    printf("STR: %s -> OP: %d     ADDR: %d \n", op->op_str, (i_code << 16) | get_opcode(op->op_str), exec->length);
    exec->code[exec->length++] = (i_code << 16) | get_opcode(op->op_str);
    exec->length += i;
}

// this function goes through the token array changes instructions according
// to the operands, changes labels and registers to opcodes
int assemble(executable_t *exec) {
    int index = tok_start;

    while (index < tok_cnt) {
        char *tok = tokens[index++];
    
        op_t *op = is_instruction(tok);

        if (op) {
            process_inst(exec, op, &index);
        }
        else {
            printf("literal value: %d \n", atoi(tok));
            exec->code[exec->length++] = atoi(tok);
        }
    }
}

executable_t *vm_load(char *fn) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int lno = 1;

    executable_t *exec = malloc(sizeof(executable_t));

    exec->code = malloc(RAM_SZ);
    exec->entry  = 7;

    add_label(exec, "$A",  A);
    add_label(exec, "$B",  B);
    add_label(exec, "$C",  C);
    add_label(exec, "$D",  D);
    add_label(exec, "$SP", SP);
    add_label(exec, "$BP", BP);

    exec->length = 7;

    fp = fopen(fn, "r");
    if (!fp) return NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[strspn(line, " \t\v\r\n")] != '\0') 
            tokenize(exec, line);
    }

    fclose(fp);

    assemble(exec);

    return exec;
}

// TODO: make sure to free the memory we used!
void vm_unload(executable_t *e) {
    if (e) free(e);
}
