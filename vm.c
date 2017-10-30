#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "ops.h"

static int *ram;
static cpu_t *cpu;

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
 
void dump_cpu() {
    printf("pc: %d \n", cpu->pc);
    printf("a: %d \n", cpu->a);
    printf("b: %d \n", cpu->b);
    printf("c: %d \n", cpu->c);
}

void vm_execute(executable_t *e) {
    ram = malloc(RAM_SZ); 
    cpu = malloc(sizeof(cpu_t)); 
    
    memcpy(ram, e->code, (e->length * sizeof(int)));
    cpu->pc = e->entry;

    int running = 1;
    int op, val;
    int *reg;

    while (running) {
        dump_cpu();
        op = ram[cpu->pc];

        printf("OP: %d \n \n", op);

        switch (op) {
            case NOP:
                cpu->pc++;
                break;

            case ADD:
                val = ram[++cpu->pc];
                reg = get_register(ram[++cpu->pc]);

                *reg += val;
                break;

            case SUB:
                val = ram[++cpu->pc];
                reg = get_register(ram[++cpu->pc]);

                *reg -= val;
                break;

            case STORE:
                val = ram[++cpu->pc];
                reg = get_register(ram[++cpu->pc]);

                *reg = val;
                break;

            case LHOP:
                cpu->pc = ram[cpu->pc + 1] - 1;
                break;

            case EXIT:
                running = 0;
                break;

            default: 
                printf("unrecognized op... oh no");
                running = 0;
        }

        cpu->pc++;
    }
}

