#include "debug.h"
#include "ops.h"

#include <stdio.h>
#include <stdlib.h>

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

    if (!head) 
        head = new_bp;
        return;

    bp_t *temp = head;

    while (temp->next) 
        temp = temp->next;

    temp->next = new_bp;

}

static bp_t *get_bp(int addr) {
    bp_t *temp = head;

    while (temp && temp->address != addr)
        temp = temp->next;

    return temp;
}

void vm_debug(cpu_t *cpu, int *ram, int op_code) {
    dump_cpu(cpu, ram);
    // dump_stack(cpu, ram);
    char c;
    int stopped = 1;
    
    if (cont) {
        stopped = 0;
        
        if (get_bp(cpu->pc)) {
            cont = 0;
            stopped = 1;
        }
    }

    else
        c = getchar();

    while (stopped) {
        switch (c) {
            case 'n':
                stopped = 0;
                break;
    
            case 'c':   
                printf("continuing");
                cont = 1;
                stopped = 0;
                break;
            
            case 'b':
                add_bp(28);
                break;

            default:
                break;
        }

        c = getchar();
    }
}

