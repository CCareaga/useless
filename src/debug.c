#include "debug.h"
#include "ops.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static int cont = 0;

typedef struct b_point {
    int address;
    struct b_point *next;
} bp_t;

bp_t *head = NULL;

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
static void dump_cpu(cpu_t *cpu, int *ram) {
    printf("========= CPU ==========\n");
    printf("A: %d \n", ram[A]);
    printf("B: %d \n", ram[B]);
    printf("C: %d \n", ram[C]);
    printf("D: %d \n", ram[D]);
    printf("E: %d \n", ram[E]);

    printf("PC: %d \n", cpu->pc);
    printf("OP: %s \n", operations[(uint16_t) ram[cpu->pc]].op_str);
    printf("========================\n\n");
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

static void new_bp(char **toks, cpu_t *cpu) {
    static int bp_num = 1;
    int addr = 0;
    addr = (toks[1]) ? atoi(toks[1]) : cpu->pc;
    printf("%d: bp at: %d \n", bp_num++, addr);
    add_bp(addr);
}

static char **tokenize(char *line) {
    int in_word = 0;
    int index = 0;
    char *start;
    
    char **tokens = malloc(sizeof(char *) * 2);

    while (*line != '\0' && index < 2) {
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
// this is probably a bad way to do it, also it is a mess but that's okay 
void vm_debug(cpu_t *cpu, int *ram, int op_code) {
    // dump_stack(cpu, ram);

    char c = 0;
    char *line = NULL;
    char **toks;
    size_t size;

    int stopped = 1;
    
    if (cont) {
        stopped = 0;
        
        if (get_bp(cpu->pc)) {
            cont = 0;
            stopped = 1;
            dump_cpu(cpu, ram);
            getline(&line, &size, stdin);
        }
    }
    else {
        system("clear"); 
        dump_cpu(cpu, ram);
        getline(&line, &size, stdin);
    }
    
    if (line) {
        toks = tokenize(line);
        c = toks[0][0];
    }

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
                new_bp(toks, cpu);
                stopped = 1;
                break;

            default:
                stopped = 0;
                break;
        }
        
        if (toks) free(toks);

        if (stopped) {
            getline(&line, &size, stdin);
            toks = tokenize(line); 
            c = toks[0][0];
        }

        system("clear");
    }
}

