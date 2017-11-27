#ifndef _OPS_H
#define _OPS_H

#include "instruction.h"

typedef struct {
    int argc;           // arg count
    const char *op_str; // operation name
    int (*func) (cpu_t *cpu, int *ram, uint16_t type);
} op_t;

extern op_t operations[];

enum operands {
    L = 0x1,
    M = 0x2,
    R = 0x4,
};

enum regs {
    A = 1,
    B,
    C,
    D,
    E,
    SP,
    BP
};

op_t *is_instruction(char *word);

#endif // _OPS_H
