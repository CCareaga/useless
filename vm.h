#ifndef _VM_H
#define _VM_H

#include "interpreter.h"

#define RAM_SZ 4096

typedef struct {
    int cmp : 1;
} flags_t;

typedef struct {
    int pc; // program counter

    int sp; // stack pointer
    int bp; // base pointer

    int a;  // reg a
    int b;  // reg b
    int c;  // reg c

    flags_t flgs;
} cpu_t;

typedef struct {
    int *ram; 
    cpu_t *cpu; 
} vm_t;

void vm_execute(executable_t *e);
int *get_register(int code);

#endif // _VM_H
