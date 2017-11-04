#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
	{0, "NOP", nop},
    {2, "ADD", add},
    {2, "SUB", sub},
    {0, "EXIT", vexit},
    {2, "LOAD", NULL},
    {2, "STORE", store},
    {1, "LHOP", lhop},
    {1, "LHOPT", lhopt},
    {1, "LHOPF", lhopf},
    {1, "PRINTR", printr},
    {1, "PUSH", push},
    {0, "POP", pop},
    {2, "EQ", equ}
};

rcode_t registers[] = {
    {"A"},
    {"B"},
    {"C"},
    {"SP"},
    {"BP"}
};

// searches through the arrays of operations and registers to determine
// the opcode for a given word. if no opcode is found via arrays, atoi is used
int get_opcode(char *word) {
    int op_count  = sizeof(operations) / sizeof(op_t); 
    int reg_count = sizeof(registers) / sizeof(rcode_t); 
    int i;

    for (i = 0; i < op_count; i++) {
        if (strcmp(operations[i].op_str, word) == 0) {
            return i;
        }
    }

    for (i = 0; i < reg_count; i++) {
        if (strcmp(registers[i].name, word) == 0) {
            return i + 1;
        }
    }

    return atoi(word);
}
