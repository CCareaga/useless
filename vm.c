#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "ops.h"

static int *ram;
static cpu_t *cpu;

// given an integer opcode, the corresponding register is returned.
int *get_register(int code) {
    switch (code) {
        case 1:
            return &cpu->a;

        case 2:
            return &cpu->b;

        case 3:
            return &cpu->c;

        case 4:
            return &cpu->sp;

        case 5:
            return &cpu->bp;

        default:
            return NULL;
    }
}

void dump_stack(cpu_t *c) {
    int i = c->sp;
    
    printf("======== STACK ========\n");
    while (i < RAM_SZ) {
        printf("%d: %d\n", i, ram[i]);
        i++;
    }
    printf("=======================\n\n");
}

// print the program counter and registers
void dump_cpu() {

    printf("========= CPU ==========\n");
    printf("pc: %d \n", cpu->pc);
    printf("a:  %d \n", cpu->a);
    printf("b:  %d \n", cpu->b);
    printf("c:  %d \n", cpu->c);

    printf("sp: %d \n", cpu->sp);
    printf("bp: %d \n", cpu->bp);
    printf("========================\n\n");
}

// executes a given executable
void vm_execute(executable_t *e) {
    ram = malloc(RAM_SZ); 
    cpu = malloc(sizeof(cpu_t)); 

    memset(ram, 0, RAM_SZ);
    memset(cpu, 0, sizeof(cpu_t));
    
    memcpy(ram, e->code, (e->length * sizeof(int)));
    cpu->pc = e->entry;

    cpu->sp = RAM_SZ - 1;
    cpu->bp = RAM_SZ - 1;

    int op;
    int running = 1;

    while (running) {
        dump_cpu();
        // dump_stack(cpu);

        op = ram[cpu->pc];
        running = operations[op].func(cpu, ram);
        cpu->pc++;
        getchar();
    }

    free(ram);
    free(cpu);
}

