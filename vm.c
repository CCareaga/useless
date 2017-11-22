#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "ops.h"

static int *ram;
static cpu_t *cpu;

void dump_stack(cpu_t *c) {
    int i = ram[4];

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
    printf("A: %d \n", ram[1]);
    printf("B: %d \n", ram[2]);
    printf("C: %d \n", ram[3]);

    printf("PC: %d \n", cpu->pc);
    printf("OP: %s \n", operations[(uint16_t) ram[cpu->pc]].op_str);
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

    ram[4] = RAM_SZ;
    ram[5] = RAM_SZ;

    int opcode;
    uint16_t operation, operands;
    int running = 1;

    while (running) {
        dump_cpu();
        dump_stack(cpu);

        opcode = ram[cpu->pc];
        operation = (uint16_t) opcode;
        operands = opcode >> 16;

        running = operations[operation].func(cpu, ram, operands);
        cpu->pc++;

        getchar();
    }

    free(ram);
    free(cpu);
}

