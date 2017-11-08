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

extern op_t operations[];

op_t *is_instruction(char *word);
int is_register(char *word);
int get_opcode(char *word);

#endif // _OPS_H
