#ifndef _DEBUG_H
#define _DEBUG_H

#include "vm.h"
#include "interpreter.h"

void vm_debug(executable_t *exec, cpu_t *cpu, int *ram, int opcode);

#endif // _DEBUG_H
