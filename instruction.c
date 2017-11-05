#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ops.h"
#include "vm.h"

int nop(cpu_t *cpu, int *ram) {
    return 1;
}

// MATH INSTRUCTIONS =============================
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
// ===============================================

// STORAGE INSTRUCTIONS ==========================
int storr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg = val;
	return 1;
}

int storl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];
    ram[lbl] = val;

    return 1;
}
// ===============================================

// MOVE INSTRUCTIONS =============================
int mvrl(cpu_t *cpu, int *ram) {
    int *reg = get_register(ram[++cpu->pc]);
    int lbl = ram[++cpu->pc];
    ram[lbl] = *reg;
    return 1;
}

int mvlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);
    *reg = ram[lbl];
    return 1;
}

int mvrr(cpu_t *cpu, int *ram) {
    int *r1 = get_register(ram[++cpu->pc]);
    int *r2 = get_register(ram[++cpu->pc]);
    *r2 = *r1;
    return 1;
}

int mvll(cpu_t *cpu, int *ram) {
    int l1 = ram[++cpu->pc];
    int l2 = ram[++cpu->pc];
    ram[l2] = ram[l1];
    return 1;
}
// ===============================================

// DEREF INSTRUCTIONS ============================
int drefr(cpu_t *cpu, int *ram) {
    int *r1 = get_register(ram[++cpu->pc]);
    int *r2 = get_register(ram[++cpu->pc]);

    *r2 = ram[*r1];
    return 1;
}

int drefl(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg = ram[lbl];
    return 1;
}
// ===============================================

// HOP INSTRUCTIONS ==============================
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

int lhopf(cpu_t *cpu, int *ram) {
	if (!cpu->flgs.cmp)
		cpu->pc = ram[cpu->pc + 1] - 1;
	else
		++cpu->pc;
	return 1;
}
// ===============================================

// PRINT INSTRUCTIONS ============================
int printr(cpu_t *cpu, int *ram) {
	int *reg = get_register(ram[++cpu->pc]);
	putchar(*reg);
	return 1;
}

int printl(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
	putchar(ram[lbl]);
	return 1;
}
// ===============================================

 // STACK INSTRUCTIONS ===========================
int push(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    ram[--cpu->sp] = val;
    return 1;
}

int pushr(cpu_t *cpu, int *ram) {
	int *reg = get_register(ram[++cpu->pc]);
    ram[--cpu->sp] = *reg;
    return 1;
}

int pop(cpu_t *cpu, int *ram) { 
    if (cpu->sp < (RAM_SZ - 1)) {
        cpu->sp++; 
    }
    return 1;
}

int popr(cpu_t *cpu, int *ram) { 
	int *reg = get_register(ram[++cpu->pc]);
    *reg = ram[cpu->sp];

    if (cpu->sp < (RAM_SZ - 1)) {
        cpu->sp++; 
    }
    return 1;
}
// ===============================================

int equ(cpu_t *cpu, int *ram) {
	int val = ram[++cpu->pc];
	int *reg = get_register(ram[++cpu->pc]);

	cpu->flgs.cmp = (val == *reg);
	return 1;
}

int vexit(cpu_t *cpu, int *ram) {
	return 0;
}

