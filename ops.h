#ifndef _OPS_H
#define _OPS_H

#include "instruction.h"

typedef struct {
    int argc;           // arg count
    const char *op_str; // operation name
	int (*func) (cpu_t *cpu, int *ram, uint16_t type);
} op_t;

typedef struct {
    const char *name;   // register name
} rcode_t;

extern op_t operations[];

enum operands {
    L = 0x1,
    M = 0x2,
    R = 0x4,
};

op_t *is_instruction(char *word);
int is_register(char *word); int get_opcode(const char *word);

#endif // _OPS_H
