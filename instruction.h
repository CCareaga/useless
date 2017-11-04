#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include "vm.h"

int nop(cpu_t *cpu, int *ram);
int add(cpu_t *cpu, int *ram);
int sub(cpu_t *cpu, int *ram);
int store(cpu_t *cpu, int *ram);
int lhop(cpu_t *cpu, int *ram);
int lhopt(cpu_t *cpu, int *ram);
int lhopf(cpu_t *cpu, int *ram);
int printr(cpu_t *cpu, int *ram);
int push(cpu_t *cpu, int *ram);
int pop(cpu_t *cpu, int *ram);
int equ(cpu_t *cpu, int *ram);
int vexit(cpu_t *cpu, int *ram);

#endif
