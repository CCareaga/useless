#include "ops.h"
#include "interpreter.h"
#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int tok_start = BP;
static char *tokens[RAM_SZ];
static int tok_cnt = BP;

typedef void *(*state_t) (executable_t *exec, char *c, char **start);

static void *state0(executable_t *exec, char *c, char **start);
static void *state1(executable_t *exec, char *c, char **start);
static void *state2(executable_t *exec, char *c, char **start);

// ========================================================================
//                     LINE NUMBER FUNCTIONS 
// ========================================================================

// this function adds a new line num struct to the executable
void add_line(executable_t *exec, char *fname, int lno, int start, int end, char *line) {
    lnum_t *ln = malloc(sizeof(lnum_t));

    char *fn = strdup(fname);
    ln->fname = fn;
    ln->num = lno;
    ln->start = start;
    ln->stop = end;
    ln->line = line;
    ln->next = NULL;
    
    lnum_t *current = exec->lnums;

    while (current && current->next) 
        current = current->next; 
    
    if (current) 
        current->next = ln;
    else
        exec->lnums = ln;
}

// ========================================================================
//                        LABEL RELATED FUNCTIONS 
// ========================================================================

// traverses the label linked list to determine if a word in the asm
// is a label. if it is, the corresponding address is returned, otherwise 0
int is_label(executable_t *exec, char *word) {
    lnode_t *current = exec->labels;

    while (current && strcmp(current->name, word) != 0) {
        current = current->next;
    }

    return (current) ? current->address : 0;
}

// this function adds a new lbl to the executable mapped to the provided address
void add_label(executable_t *exec, char *name, int addr) {
    lnode_t *lbl = malloc(sizeof(lnode_t));

    char *lbl_name = strdup(++name);
    lbl->name = lbl_name;
    lbl->address = addr;
    lbl->next = NULL;

    lnode_t *head = exec->labels;
    
    exec->labels = lbl;
    lbl->next = head;
}

// ========================================================================
//                         COMPILATION FUNCTIONS 
// ========================================================================

// STATE MACHINE ==========================================================
//                    space
//                    +----+
//                    |    |
//     letter       +-+----v-+       qoute
//      +-----------+        +----------+
//      |           | state0 |          |
//      |    +------>        |          |
//      |    |space +--------+          |
//      |    |                          |
//    +-v----+-+      qoute      +------v-+
//    |        <-----------------+        |
//    | state1 |                 | state2 |
//    |        +----------------->        |
//    +-+----^-+      qoute      +-^----+-+
//      |    |                     |    |
//      +----+                     +----+
//      letter                    anything
// ----------------------------------------------------

// this function runs the state machine, the tokens in the src file
// are saved in a static array on the heap, this gets called on every line
// returns 1 on error (non-accept state) and 0 otherwise
int tokenize(executable_t *exec, char *line) {
    state_t state = state0;
    char *start;

    while (*line && *line != '~') {
        state = (state_t) (*state)(exec, line, &start);
        line++;
    }

    return (state == state2);
}

// this converts an escape character into the actual ascii for
// the escape sequence eg. n => 10 t => 11
int convert_escape(char c) {
    switch (c) {
        case 'n':
            return 10;

        case 't':
            return 11;

        default:
            return (int) c;
    }
}

// this function adds a string into the programs memory. we skip
// the first letter because its a qoute, we also add the null terminator to memory
// we also account for escape sequences (works alright I guess)
static void add_string(executable_t *exec, char *str) {
    int escape = 0;
    char buf[5];
   
    str++;
    while (*str != '"') {
        if (escape) {
            sprintf(buf, "%d", convert_escape(*str));
            tokens[tok_cnt++] = strdup(buf); 
            escape = 0;
        }

        else if (*str == '\\') 
            escape = 1;

        else {
            sprintf(buf, "%d", (int) *str);
            tokens[tok_cnt++] = strdup(buf); 
        }

        str++;
    }

    tokens[tok_cnt++] = strdup("0"); 
}
// this function gets called on each token in the src file.
// it adds labels and adds the entry point of the program. for every
// other token it saves the token on the heap and adds it to the token arr
static void add_token(executable_t *exec, char *token) {
    if (*token == '$') 
        add_label(exec, token, tok_cnt + 1);   

    else if (*token == '"') 
        add_string(exec, token);

    else if (!strcmp(token, "entry"))
        exec->entry = tok_cnt + 1;

    else 
        tokens[tok_cnt++] = strdup(token); 
}

// state0 start state, we loop on spaces and move states when
// we see a letter or a quote, if we see non-space we save the start
static void *state0(executable_t *exec, char *c, char **start) {
    if (isspace(*c)) 
        return state0;

    else if (*c == '"') {
        *start = c; 
        return state2;
    }

    else {
        *start = c;
        return state1;
    }
}

// state1 means we have seen the start of a word and now we are
// consuming characters until we see a space or a quote
static void *state1(executable_t *exec, char *c, char **start) {
    if (isspace(*c)) {
        *c = '\0';
        add_token(exec, *start);
        return state0;
    }

    else if (*c == '"') {
        return state2;
    }

    else 
        return state1;
}

// state2 means we have seen one quote, we loop on all characters 
// until we see the ending quote, if we end in this state it means
// we have seen mismatched qoutes.
static void *state2(executable_t *exec, char *c, char **start) {
    if (*c == '"') {
        return state1;
    }
    else 
        return state2;
}

// this function goes through the instructions and translates them
// to op codes depending on the operands (L = literal, R = reference, M = memory)
void process_inst(executable_t *exec, op_t *op, int *index) {
    int i = 0;

    int opcode;
    int i_code = 0;

    char *operand;

    for (i = 0; i < op->argc; i++) {
        operand = tokens[(*index)++];

        int lbl = is_label(exec, operand);
        
        if (operand[0] == '*') {
            i_code |= R << (i * 4);
            opcode = is_label(exec, operand + 1);
        }

        else if (operand[0] == '&') {
            i_code |= L << (i * 4);
            opcode = is_label(exec, operand + 1);
        }

        else if (lbl) {
            i_code |= M << (i * 4);
            opcode = lbl;
        }

        else {
            i_code |= L << (i * 4);
            opcode = atoi(operand);
        }

        exec->code[exec->length + i + 1] = opcode;
        free(operand);
    }

    exec->code[exec->length++] = (i_code << 16) | (int) (op - operations);
    exec->length += i;
}

// this function goes through the token array and either processes instructions
// or translates the token to a literal. the tokens are then free'd
void assemble(executable_t *exec) {
    int index = tok_start;

    while (index < tok_cnt) {
        char *tok = tokens[index++];
    
        op_t *op = is_instruction(tok);

        if (op) 
            process_inst(exec, op, &index);

        else 
            exec->code[exec->length++] = (tok[0] == '&') ? is_label(exec, tok + 1) : atoi(tok);

        free(tok);
    }
}

// this function creates an executable struct, adds registers,
// and translates the given files into "byte" code
executable_t *vm_load(char **fnames, int dbg) {
    int err = 0;

    executable_t *exec = malloc(sizeof(executable_t));

    exec->code = malloc(RAM_SZ);
    
    exec->labels = NULL;
    exec->lnums = NULL;

    add_label(exec, "$a",  A);
    add_label(exec, "$b",  B);
    add_label(exec, "$c",  C);
    add_label(exec, "$d",  D);
    add_label(exec, "$e",  E);
    add_label(exec, "$sp", SP);
    add_label(exec, "$bp", BP);
    add_label(exec, "$r", RET);

    exec->length = BP + 1;
    exec->entry  = BP + 1;
    exec->debug  = dbg;
    
    while(*fnames) {
        FILE *fp;
        char *line = NULL;
        char *saved;
        size_t len = 0;
        ssize_t read;

        int lno = 1;
        int start;

        fp = fopen(*fnames, "r");
        if (!fp) 
            return NULL;

        while ((read = getline(&line, &len, fp)) != -1 && !err) {
            start = tok_cnt + 1;
            if (dbg)
                saved = strdup(line); 

            if (line[strspn(line, " \t\v\r\n")] != '\0') {
                err = tokenize(exec, line);
                if (err) 
                    fprintf(stderr, "%s:%d - mistmatched quotes \n", *fnames, lno);
            }

            if (dbg)
                add_line(exec, *fnames, lno++, start, tok_cnt + 1, saved);
        }

        fclose(fp);
        fnames++;
    }
    
    if (!err) 
        assemble(exec);

    return (err) ? NULL : exec;    
}

// TODO: make sure to free the memory we used!
void vm_unload(executable_t *e) {
    
    lnode_t *t1;
    lnum_t *t2;

    while (e->labels) {
        t1 = e->labels;    
        e->labels = e->labels->next;
        free(t1);
    }

    while (e->lnums) {
        t2 = e->lnums;    
        e->lnums = e->lnums->next;
        free(t2);
    }
        
    free(e);
}
