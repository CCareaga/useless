#ifndef _OPS_H
#define _OPS_H

#include "instruction.h"

typedef struct {
    int argc;           // arg count
    const char *op_str; // operation name
	int (*func) (cpu_t *cpu, int *ram);
} op_t;

typedef struct {
    const char *name;   // register name
} rcode_t;

enum {
    NOP,
    ADD,
    SUB,
    EXIT,
    LOAD,
    STORE,
    LHOP,
    LHOPT,
    PRINTR,
    EQ,
};

extern op_t operations[];

int get_opcode(char *word);

#endif // _OPS_H
