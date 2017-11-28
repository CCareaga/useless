#include "debug.h"
#include "ops.h"

#include <stdio.h>

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

void vm_debug(cpu_t *cpu, int *ram, int op_code) {
    dump_cpu(cpu, ram);
    dump_stack(cpu, ram);
    char c = getchar();
}

