#include "debug.h"
#include "ops.h"
#include "interpreter.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>

#define MAX_TOK 3

static int cont = 0;

typedef struct b_point {
    int address;
    struct b_point *next;
} bp_t;

bp_t *head = NULL;

// traverses the lnum linked list to determine the addr range of a line
lnum_t *get_lnum(executable_t *exec, char *fn, int lno) {
    lnum_t *current = exec->lnums;

    while (current && !(strcmp(basename(current->fname), fn) == 0 && current->num == lno))
        current = current->next;

    return current;
}

lnum_t *get_lnum_by_addr(executable_t *exec, int addr) {
    lnum_t *current = exec->lnums;

    while (current && !(current->start == addr && current->start != current->stop))
        current = current->next;

    return current;
}

// prints the debugger prompt :-)
static void print_prompt() {
    printf("udb >> ");
}

// print the stack and the stack pointers
static void dump_stack(cpu_t *cpu, int *ram) {
    int i = ram[SP];

    printf("======== STACK ========\n");
    while (i < RAM_SZ) {
        printf("%d: %d\n", i, ram[i]);
        i++;
    }

    printf("\nSP: %d \n", ram[SP]);
    printf("BP: %d \n", ram[BP]);
    printf("=======================\n\n");
}

// print the program counter and registers
static void dump_cpu(executable_t *exec, cpu_t *cpu, int *ram) {
    printf("========= CPU ================\n");
    printf("A: %d \n", ram[A]);
    printf("B: %d \n", ram[B]);
    printf("C: %d \n", ram[C]);
    printf("D: %d \n", ram[D]);
    printf("E: %d \n", ram[E]);

    printf("PC: %d \n", cpu->pc);
    lnum_t *ln = get_lnum_by_addr(exec, cpu->pc);
    printf("==============================\n");
    printf("%s : %d \n\n", ln->fname, ln->num);
    printf("%s \n", ln->line);
    printf("==============================\n\n");
    print_prompt();
}

static void print_lbl(executable_t* exec, int *ram, char **toks) {
    int lbl;
    int val;
    int deref = 0;

    if (toks[1]) {
        if (toks[1][0] == '*') {
            deref = 1;
            (toks[1])++;
        }
            
        lbl = is_label(exec, toks[1]);

        if (lbl) { 
            val = (deref) ? ram[ram[lbl]] : ram[lbl];
            printf("%s: %d \n", toks[1], val);
        }
        else
            printf("no label with name: %s \n", toks[1]);
    }
    else
        printf("print takes one argument\n");
}

// add a new break point to the linked list
static void add_bp(int addr) {
    bp_t *new_bp = malloc(sizeof(bp_t));
    new_bp->address = addr;
 
    new_bp->next = head;
    head = new_bp;
}

// retrieve the bp node for a certain address if one exists
static bp_t *get_bp(int addr) {
    bp_t *temp = head;

    while (temp && temp->address != addr)
        temp = temp->next;

    return temp;
}

// add a new break point to the break point list. uses the tokens
// to determine whether to set on a line num, label or current pos
static void new_bp(executable_t *exec, char **toks, cpu_t *cpu) {
    static int bp_num = 1;
    int addr = 0;

    if (toks[2]) {
        lnum_t *ln = get_lnum(exec, toks[1], atoi(toks[2]));
        addr = (ln) ? ln->start : 0;
    }
    else if (toks[1]) {
        addr = is_label(exec, toks[1]);
        if (addr == 0) 
            addr = atoi(toks[1]);
    }
    else {
        addr = cpu->pc;
    }
        
    if (addr) {
        printf("%d: bp at: %d \n", bp_num++, addr);
        add_bp(addr);
    }
    else 
        printf("cannot set breakpoint \n");
}

static char **tokenize(char *line) {
    int in_word = 0;
    int index = 0;
    char *start;
    
    char **tokens = malloc(sizeof(char *) * MAX_TOK);
    memset(tokens, 0, sizeof(char *) * MAX_TOK);

    while (*line != '\0' && index < MAX_TOK) {
        if (!in_word) {
            if (!(isspace(*line))) {
                start = line;
                in_word = 1;
            }
        }
        else {
            if (isspace(*line)) {
                *line = '\0';
                tokens[index++] = start; 
                in_word = 0;
            }
        }

        line++;
    }

    return tokens;
}

// this function inplements debug functionality, it runs after every instruction
// this is probably a bad way to do it, also it is a big mess but that's okay 
void vm_debug(executable_t *exec, cpu_t *cpu, int *ram, int op_code) {
    char c = 0;
    char *line = NULL;
    char **toks = NULL;
    size_t size;

    int stopped = 1;
    
    if (cont) {
        stopped = 0;
        
        if (get_bp(cpu->pc)) {
            cont = 0;
            stopped = 1;
            system("clear"); 
            dump_cpu(exec, cpu, ram);
            getline(&line, &size, stdin);
        }
    }
    else {
        system("clear"); 
        dump_cpu(exec, cpu, ram);
        getline(&line, &size, stdin);
    }
    
    if (line && line[0] != 10) {
        toks = tokenize(line);
        c = toks[0][0];
    }
    else 
        c = 'n';

    while (stopped) {

        switch (c) {
            case 'n':
                stopped = 0;
                break;
    
            case 'c':   
                printf("continuing\n");
                cont = 1;
                stopped = 0;
                break;
            
            case 'b':
                new_bp(exec, toks, cpu);
                print_prompt();
                stopped = 1;
                break;

            case 'p':
                print_lbl(exec, ram, toks);
                print_prompt();
                stopped = 1;
                break;

            case 's':
                system("clear");
                dump_stack(cpu, ram);
                print_prompt(); 
                stopped = 1;
                break;

            default:
                printf("unrecognized command! \n");
                print_prompt();
                stopped = 1;
                break;
        }
        
        if (toks) {
            free(toks);
            toks = NULL;
        }

        if (stopped) {
            getline(&line, &size, stdin);
            if (line && line[0] != 10) {
                toks = tokenize(line); 
                c = toks[0][0];
            }
            else 
                c = 'n';
        }
    }
}

