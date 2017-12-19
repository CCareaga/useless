#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "ops.h"
#include "debug.h"

static int *ram;
static cpu_t *cpu;

static int debug = 0;

// executes a given executable_t
void vm_execute(executable_t *e) {
    ram = malloc(RAM_SZ); 
    cpu = malloc(sizeof(cpu_t)); 

    memset(ram, 0, RAM_SZ);
    memset(cpu, 0, sizeof(cpu_t));
     
    memcpy(ram, e->code, (e->length * sizeof(int)));
    cpu->pc = e->entry;

    ram[SP] = RAM_SZ;
    ram[BP] = RAM_SZ;

    int opcode;
    uint16_t operation, operands;
    int running = 1;

    while (running) {
        opcode = ram[cpu->pc];
        operation = (uint16_t) opcode;
        operands = opcode >> 16;
        
        // vm_debug(e, cpu, ram, opcode);

        running = operations[operation].func(cpu, ram, operands);
        cpu->pc++;
    }

    free(ram);
    free(cpu);
}

// unused function used to read a binary file assembled by assembly.c
executable_t *read_bin(char *fn) {
    
    FILE *fp = fopen(fn, "rb");
    if (!fp) return NULL;

    int magic = 0;

    executable_t *exec = malloc(sizeof(executable_t));
    exec->code = malloc(sizeof(int) * RAM_SZ);
    
    fread(&magic, sizeof(int), 1, fp);

    if (magic != 0xd00ddead) {
        fclose(fp);
        return NULL;
    }

    fread(&exec->length, sizeof(int), 1, fp);
    fread(&exec->entry, sizeof(int), 1, fp);
    fread(exec->code, sizeof(int), exec->length, fp);

    fclose(fp);

    return exec;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    executable_t *exec = vm_load(&argv[1]);

    // NOTE: assembler.c is currently unused but it is possible to save useless 
    // programs as binary files and read them into an exec struct using these lines
    // executable_t *exec = read_bin(argv[1]);
    // if (!exec) return -1;

    vm_execute(exec);
    vm_unload(exec);
}   

