#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ops.h"
#include "vm.h"

int nop(cpu_t *cpu, int *ram) {
    return 1;
}

// MATH INSTRUCTIONS =============================

// literal and register
int addr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg += val;
    return 1;
}

int subr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg -= val;
    return 1;
}

int mulr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg *= val;
    return 1;
}

int divr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg /= val;
    return 1;
}

int modr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg %= val;
    return 1;
}

// literal and label
int addl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    ram[lbl] += val;
    return 1;
}

int subl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    ram[lbl] -= val;
    return 1;
}

int mull(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    ram[lbl] *= val;
    return 1;
}

int divl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    ram[lbl] /= val;
    return 1;
}

int modl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    ram[lbl] %= val;
    return 1;
}

// label and register
int addlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg += ram[lbl];
    return 1;
}

int sublr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg -= ram[lbl];
    return 1;
}

int mullr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg *= ram[lbl];
    return 1;
}

int divlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg /= ram[lbl];
    return 1;
}

int modlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    *reg %= ram[lbl];
    return 1;
}

// register and label
int addrl(cpu_t *cpu, int *ram) {
    int *reg = get_register(ram[++cpu->pc]);
    int lbl = ram[++cpu->pc];

    ram[lbl] += *reg;
    return 1;
}

int subrl(cpu_t *cpu, int *ram) {
    int *reg = get_register(ram[++cpu->pc]);
    int lbl = ram[++cpu->pc];

    ram[lbl] -= *reg;
    return 1;
}

int mulrl(cpu_t *cpu, int *ram) {
    int *reg = get_register(ram[++cpu->pc]);
    int lbl = ram[++cpu->pc];

    ram[lbl] *= *reg;
    return 1;
}

int divrl(cpu_t *cpu, int *ram) {
    int *reg = get_register(ram[++cpu->pc]);
    int lbl = ram[++cpu->pc];

    ram[lbl] /= *reg;
    return 1;
}

int modrl(cpu_t *cpu, int *ram) {
    int *reg = get_register(ram[++cpu->pc]);
    int lbl = ram[++cpu->pc];

    ram[lbl] %= *reg;
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

// COMPARISONS ===================================

// literal and register
int eqr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (val == *reg);
    return 1;
}

int neqr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (val != *reg);
    return 1;
}

int ltr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (val < *reg);
    return 1;
}

int lter(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (val <= *reg);
    return 1;
}

int gtr(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (val > *reg);
    return 1;
}

int gter(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (val >= *reg);
    return 1;
}

// literal and label
int eql(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    cpu->flgs.cmp = (val == ram[lbl]);
    return 1;
}

int neql(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    cpu->flgs.cmp = (val != ram[lbl]);
    return 1;
}

int ltl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    cpu->flgs.cmp = (val < ram[lbl]);
    return 1;
}

int ltel(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    cpu->flgs.cmp = (val <= ram[lbl]);
    return 1;
}

int gtl(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    cpu->flgs.cmp = (val > ram[lbl]);
    return 1;
}

int gtel(cpu_t *cpu, int *ram) {
    int val = ram[++cpu->pc];
    int lbl = ram[++cpu->pc];

    cpu->flgs.cmp = (val >= ram[lbl]);
    return 1;
}

// label to register cmp
int eqlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (ram[lbl] == *reg);
    return 1;
}

int neqlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (ram[lbl] != *reg);
    return 1;
}

int ltlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (ram[lbl] < *reg);
    return 1;
}

int ltelr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (ram[lbl] <= *reg);
    return 1;
}

int gtlr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (ram[lbl] > *reg);
    return 1;
}

int gtelr(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    int *reg = get_register(ram[++cpu->pc]);

    cpu->flgs.cmp = (ram[lbl] >= *reg);
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

int pushl(cpu_t *cpu, int *ram) {
    int lbl = ram[++cpu->pc];
    ram[--cpu->sp] = ram[lbl];
    return 1;
}

int pop(cpu_t *cpu, int *ram) { 
    if (cpu->sp < (RAM_SZ - 1))
        cpu->sp++; 
    return 1;
}

int popr(cpu_t *cpu, int *ram) { 
    int *reg = get_register(ram[++cpu->pc]);
    *reg = ram[cpu->sp];

    if (cpu->sp < (RAM_SZ - 1)) 
        cpu->sp++; 

    return 1;
}

int popl(cpu_t *cpu, int *ram) { 
    int lbl = ram[++cpu->pc];
    ram[lbl] = ram[cpu->sp];

    if (cpu->sp < (RAM_SZ - 1)) 
        cpu->sp++; 

    return 1;
}
// ===============================================

int vexit(cpu_t *cpu, int *ram) {
    return 0;
}

