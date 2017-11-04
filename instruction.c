#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ops.h"
#include "vm.h"

int nop(cpu_t *cpu, int *ram) {
    return 1;
}

int add(cpu_t *cpu, int *ram) {
	int val = ram[++cpu->pc];
	int *reg = get_register(ram[++cpu->pc]);

    *reg += val;
	return 1;
}

int sub(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
	int *reg = get_register(ram[++cpu->pc]);

	*reg -= val;
	return 1;
}

int store(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg = val;
	return 1;
}

int lhop(cpu_t *cpu, int *ram) {
	cpu->pc = ram[cpu->pc + 1] - 1;
	return 1;
}

int lhopt(cpu_t *cpu, int *ram) {
	if (cpu->flgs.cmp)
		cpu->pc = ram[cpu->pc + 1] - 1;
	else
		++cpu->pc;
	return 1;
}

int equ(cpu_t *cpu, int *ram) {
	int val = ram[++cpu->pc];
	int *reg = get_register(ram[++cpu->pc]);

	cpu->flgs.cmp = (val == *reg);
	return 1;
}

int printr(cpu_t *cpu, int *ram) {
	int *reg = get_register(ram[++cpu->pc]);
	putchar(*reg);
	return 1;
}

int vexit(cpu_t *cpu, int *ram) {
	return 0;
}

