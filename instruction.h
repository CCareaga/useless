#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

#include "vm.h"

int nop(cpu_t *cpu, int *ram, uint16_t type);

int vadd(cpu_t *cpu, int *ram, uint16_t type);
int vsub(cpu_t *cpu, int *ram, uint16_t type);
int vmul(cpu_t *cpu, int *ram, uint16_t type);
int vdiv(cpu_t *cpu, int *ram, uint16_t type);
int vmod(cpu_t *cpu, int *ram, uint16_t type);

int mv(cpu_t *cpu, int *ram, uint16_t type);

int dref(cpu_t *cpu, int *ram, uint16_t type);

int hop(cpu_t *cpu, int *ram, uint16_t type);
int hopt(cpu_t *cpu, int *ram, uint16_t type);
int hopf(cpu_t *cpu, int *ram, uint16_t type);

int print(cpu_t *cpu, int *ram, uint16_t type);

int push(cpu_t *cpu, int *ram, uint16_t type);
int pop(cpu_t *cpu, int *ram, uint16_t type);

int eq(cpu_t *cpu, int *ram, uint16_t type);
int neq(cpu_t *cpu, int *ram, uint16_t type);
int lt(cpu_t *cpu, int *ram, uint16_t type);
int lte(cpu_t *cpu, int *ram, uint16_t type);
int gt(cpu_t *cpu, int *ram, uint16_t type);
int gte(cpu_t *cpu, int *ram, uint16_t type);


int call(cpu_t *cpu, int *ram, uint16_t type);
int ret(cpu_t *cpu, int *ram, uint16_t type);

int vexit(cpu_t *cpu, int *ram, uint16_t type);

#endif
