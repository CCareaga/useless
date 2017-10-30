#include "ops.h"
#include "interpreter.h"
#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int is_keyword(char *word) {
    if (strcmp(word, "ENTRY") == 0 || word[0] == '$') return 1;
    else return 0;
}

int keyword_check(char *word, executable_t *exec) {
    if (strcmp(word, "ENTRY") == 0) {
        exec->entry = exec->length;
    }
    else if (word[0] == '$') {
        exec->length--;
        lnode_t *lbl = malloc(sizeof(lnode_t));

        char *lbl_name = strdup((++word));
        lbl->name = lbl_name;
        lbl->address = exec->length;
        lbl_insert(exec, lbl); 
    }
    
    exec->length++;
    return is_keyword(word);
}

void encode(char *word, executable_t *exec) {
    int opcode;

    if (is_keyword(word)) return;
    int lbl = is_label(word, exec);

    if (lbl) opcode = lbl;
    else opcode = get_opcode(word);

    exec->code[exec->length] = opcode;
    exec->length += 1;
    printf("WORD: %s -> OPCODE: %d \n", word, opcode);
}

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

void vm_unload(executable_t *e) {
    if (e) free(e);
}

executable_t *vm_load(char *fn) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    executable_t *exec = malloc(sizeof(executable_t));

    exec->code = malloc(RAM_SZ);
    exec->length = 0;

    fp = fopen(fn, "r");
    if (!fp) return NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
        assemble(line, exec, 1);
    }

    fclose(fp);

    lnode_t *cur = exec->labels;
    while (cur) {
        printf("lbl: %s -> addr: %d \n", cur->name, cur->address);
        cur = cur->next;
    }

    exec->length = 0;

    fp = fopen(fn, "r");
    if (!fp) return NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
        assemble(line, exec, 2);
    }

    fclose(fp);

    return exec;
}
