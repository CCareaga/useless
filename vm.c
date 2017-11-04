#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "ops.h"

static int *ram;
static cpu_t *cpu;

// given an integer opcode, the corresponding register is returned.
int *get_register(int code) {
    switch (code) {
        case 1:
            return &cpu->a;

        case 2:
            return &cpu->b;

        case 3:
            return &cpu->c;

        default:
            return NULL;
    }
}

// print the program counter and registers
void dump_cpu() {
    printf("pc: %d \n", cpu->pc);
    printf("a: %d \n", cpu->a);
    printf("b: %d \n", cpu->b);
    printf("c: %d \n", cpu->c);
}

// executes a given executable
// TODO: change from switch statement to function pointers
void vm_execute(executable_t *e) {
    ram = malloc(RAM_SZ); 
    cpu = malloc(sizeof(cpu_t)); 
    
    memcpy(ram, e->code, (e->length * sizeof(int)));
    cpu->pc = e->entry;

    int running = 1;
    int op, val;
    int *reg;

    while (running) {
        // dump_cpu();
        op = ram[cpu->pc];
		running = operations[op].func(cpu, ram);
//
//        switch (op) {
//            case NOP:
//                break;
//
//            case ADD:
//                val = ram[++cpu->pc];
//                reg = get_register(ram[++cpu->pc]);
//
//                *reg += val;
//                break;
//
//            case SUB:
//                val = ram[++cpu->pc];
//                reg = get_register(ram[++cpu->pc]);
//
//                *reg -= val;
//                break;
//
//            case STORE:
//                val = ram[++cpu->pc];
//                reg = get_register(ram[++cpu->pc]);
//
//                *reg = val;
//                break;
//
//            case LHOP:
//                cpu->pc = ram[cpu->pc + 1] - 1;
//                break;
//
//            case LHOPT:
//                if (cpu->flgs.cmp)
//                    cpu->pc = ram[cpu->pc + 1] - 1;
//                else
//                    ++cpu->pc;
//                break;
//
//            case EQ:
//                val = ram[++cpu->pc];
//                reg = get_register(ram[++cpu->pc]);
//
//                cpu->flgs.cmp = (val == *reg);
//                break;
//
//            case PRINTR:
//                reg = get_register(ram[++cpu->pc]);
//                putchar(*reg);
//                break;
//                
//
//            case EXIT:
//                running = 0;
//                break;
//
//            default: 
//                printf("unrecognized op... oh no");
//                running = 0;
//        }
//
        cpu->pc++;
    }

    free(ram);
    free(cpu);
}

