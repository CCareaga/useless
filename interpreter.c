#include "ops.h"
#include "interpreter.h"
#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static char *tokens[RAM_SZ];
static int tok_cnt = 0;

// LABEL RELATED FUNCTIONS ================================================
// print out the labels in an executable.
void dump_labels(executable_t *exec) {

    lnode_t *cur = exec->labels;
    while (cur) {
        printf("lbl: %s -> addr: %d \n", cur->name, cur->address);
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
    lbl->address = addr;

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
                else
                    tokens[tok_cnt++] = strdup(start); 

                in_word = 0;
            }
        }

        line++;
    }
    
    return 0;
}

// goes through the array of tokens, converts them to op code and places
// them in the executable structure
void process_inst(executable_t *exec, op_t *op, int *index) {
    int i = 0;
    int opcode;

    int ilen = strlen(op->op_str);
    char *new_inst = malloc(ilen + 2);
    strcpy(new_inst, op->op_str);

    for (i = 0; i < op->argc; i++) {
        char *operand = tokens[(*index)++];
        int lbl = is_label(operand, exec);

        if (lbl) {
            new_inst[ilen++] = 'L';
            opcode = lbl;
        }

        else if (is_register(operand)) {
            new_inst[ilen++] = 'R';
            opcode = get_opcode(operand);
        }

        else 
            opcode = atoi(operand);

        exec->code[exec->length + i + 1] = opcode;
        free(operand);
    }

    new_inst[ilen] = 0;

    exec->code[exec->length++] = get_opcode(new_inst);
    exec->length += i;
    free(new_inst);
}

// this function goes through the token array changes instructions according
// to the operands, changes labels and registers to opcodes
// eventually there will be four cases of operands here
// *L, *R, L, D and literal
int assemble(executable_t *exec) {
    int index = 0;

    while (index < tok_cnt) {
        char *tok = tokens[index++];
    
        op_t *op = is_instruction(tok);

        if (op) {
            process_inst(exec, op, &index);
        }

        else {
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
    exec->entry  = 1;
    exec->length = 1;

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
