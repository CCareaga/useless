#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ops.h"
#include "vm.h"

int nop(cpu_t *cpu, int *ram, uint16_t type) {
    return 1;
}

int dref(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 
    printf("VAL = %d \n", val);
    ram[4] = ram[ram[val]];
    return 1;
}

int mv(cpu_t *cpu, int *ram, uint16_t type) {

    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    printf("type: %d \n", type);
    printf("type: %d \n", (M << 4) | R);

    switch (type) {
        case ((M << 4) | L):
            ram[val2] = val1;
            break;

        case ((M << 4) | R):
            ram[val2] = ram[4];
            break;

        default:
            return 0;
    }

    return 1;
}

int vexit(cpu_t *cpu, int *ram, uint16_t type) {
    return 0;
}

