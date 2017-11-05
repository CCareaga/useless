#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include "vm.h"

int nop(cpu_t *cpu, int *ram);
int add(cpu_t *cpu, int *ram);
int sub(cpu_t *cpu, int *ram);

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
int pop(cpu_t *cpu, int *ram);
int popr(cpu_t *cpu, int *ram);

int equ(cpu_t *cpu, int *ram);

int vexit(cpu_t *cpu, int *ram);

#endif
