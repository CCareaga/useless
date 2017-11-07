#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include "vm.h"

int nop(cpu_t *cpu, int *ram);

int addr(cpu_t *cpu, int *ram);
int subr(cpu_t *cpu, int *ram);
int mulr(cpu_t *cpu, int *ram);
int divr(cpu_t *cpu, int *ram);
int modr(cpu_t *cpu, int *ram);

int addl(cpu_t *cpu, int *ram);
int subl(cpu_t *cpu, int *ram);
int mull(cpu_t *cpu, int *ram);
int divl(cpu_t *cpu, int *ram);
int modl(cpu_t *cpu, int *ram);

int addrl(cpu_t *cpu, int *ram);
int subrl(cpu_t *cpu, int *ram);
int mulrl(cpu_t *cpu, int *ram);
int divrl(cpu_t *cpu, int *ram);
int modrl(cpu_t *cpu, int *ram);

int addlr(cpu_t *cpu, int *ram);
int sublr(cpu_t *cpu, int *ram);
int mullr(cpu_t *cpu, int *ram);
int divlr(cpu_t *cpu, int *ram);
int modlr(cpu_t *cpu, int *ram);

int storr(cpu_t *cpu, int *ram);
int storl(cpu_t *cpu, int *ram);

int mvrl(cpu_t *cpu, int *ram);
int mvlr(cpu_t *cpu, int *ram);
int mvrr(cpu_t *cpu, int *ram);
int mvll(cpu_t *cpu, int *ram);

int drefr(cpu_t *cpu, int *ram);
int drefl(cpu_t *cpu, int *ram);

int lhop(cpu_t *cpu, int *ram);
int lhopt(cpu_t *cpu, int *ram);
int lhopf(cpu_t *cpu, int *ram);

int printr(cpu_t *cpu, int *ram);
int printl(cpu_t *cpu, int *ram);

int push(cpu_t *cpu, int *ram);
int pushr(cpu_t *cpu, int *ram);
int pushl(cpu_t *cpu, int *ram);
int pop(cpu_t *cpu, int *ram);
int popr(cpu_t *cpu, int *ram);
int popl(cpu_t *cpu, int *ram);

int eqr(cpu_t *cpu, int *ram);
int neqr(cpu_t *cpu, int *ram);
int ltr(cpu_t *cpu, int *ram);
int lter(cpu_t *cpu, int *ram);
int gtr(cpu_t *cpu, int *ram);
int gter(cpu_t *cpu, int *ram);

int eql(cpu_t *cpu, int *ram);
int neql(cpu_t *cpu, int *ram);
int ltl(cpu_t *cpu, int *ram);
int ltel(cpu_t *cpu, int *ram);
int gtl(cpu_t *cpu, int *ram);
int gtel(cpu_t *cpu, int *ram);

int eqlr(cpu_t *cpu, int *ram);
int neqlr(cpu_t *cpu, int *ram);
int ltlr(cpu_t *cpu, int *ram);
int ltelr(cpu_t *cpu, int *ram);
int gtlr(cpu_t *cpu, int *ram);
int gtelr(cpu_t *cpu, int *ram);

int vexit(cpu_t *cpu, int *ram);

#endif
