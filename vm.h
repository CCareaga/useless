#ifndef _VM_H
#define _VM_H

#include "interpreter.h"

#define RAM_SZ 4096

typedef struct {
    int cmp : 1;
} flags_t;

typedef struct {
    int pc; // program counter
    int flg; // comparison flag
} cpu_t;

typedef struct {
    int *ram; 
    cpu_t *cpu; 
} vm_t;

void vm_execute(executable_t *e);

#endif // _VM_H
