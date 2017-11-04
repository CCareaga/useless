#include "ops.h"
#include "interpreter.h"
#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

// returns 1 if the given word is a keyword, otherwise 0
int is_keyword(char *word) {
    if (word[0] == '$') return 1;
    else return 0;
}

// inserts a new label node into the executable
void lbl_insert(executable_t *exec, lnode_t *lbl) {
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

// checks if a word is a keyword, if it is, neccesary actions are done
// this gets called on each word during the first pass of the interpreter
int keyword_check(char *word, executable_t *exec) {

    if (word[0] == '$') {
        lnode_t *lbl = malloc(sizeof(lnode_t));

        char *lbl_name = strdup((++word));
        lbl->name = lbl_name;
        lbl->address = exec->length;
        lbl_insert(exec, lbl); 
        exec->length--;
    }

    exec->length++;
    return is_keyword(word);
}

// this encodes a given word into an opcode provided it isnt a keyword 
// or a label. the opcode is then added to the executable
void encode(char *word, executable_t *exec) {
    int opcode;

    if (is_keyword(word)) return;
    int lbl = is_label(word, exec);

    if (lbl) opcode = lbl;
    else opcode = get_opcode(word);

    exec->code[exec->length] = opcode;
    printf("ADDRESS: %lu   =>   TOKEN: %s -> OPCODE: %d \n", exec->length, word, opcode);
    exec->length += 1;
}

// this parses a single line and depending on the pass number, translates
// the tokens in the line and places them in the executable
void assemble(char* line, executable_t *exec, int pass) {
    int in_word = 0; 
    char *start;

    while (*line) {
        if (!in_word) {
            if (!(isspace(*line))) {
                start = line;
                in_word = 1;
            }
        }
        else {
            if (isspace(*line)) {
                *line = '\0';

                if (pass == 1) keyword_check(start, exec);
                if (pass == 2) encode(start, exec);
                
                in_word = 0;
            }
        }

        line++;
    }
}

// TODO: make sure to free the memory we used!
void vm_unload(executable_t *e) {
    if (e) free(e);
}

// this opens a given file and runs two passes to interpret it.
// pass 1: read any labels or keywords and set there values in the executable
// pass 2: translate tokens into opcodes and replace labels with addresses
executable_t *vm_load(char *fn) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    executable_t *exec = malloc(sizeof(executable_t));

    exec->code = malloc(RAM_SZ);
    exec->entry  = 1;
    exec->length = 1;

    fp = fopen(fn, "r");
    if (!fp) return NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
        assemble(line, exec, 1);
    }


    exec->length = 1;

    rewind(fp);
    while ((read = getline(&line, &len, fp)) != -1) {
        assemble(line, exec, 2);
    }

    fclose(fp);

    return exec;
}
