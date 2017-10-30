#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
    {2, "ADD"},
    {2, "SUB"},
    {0, "EXIT"},
    {2, "LOAD"},
    {2, "STORE"},
    {1, "LHOP"},
    {1, "LHOPT"},
    {1, "PRINTR"},
    {2, "EQ"}
};

rcode_t registers[] = {
    {"A"},
    {"B"},
    {"C"}
};

// searches through the arrays of operations and registers to determine
// the opcode for a given word. if no opcode is found via arrays, atoi is used
int get_opcode(char *word) {
    int op_count  = sizeof(operations) / sizeof(op_t); 
    int reg_count = sizeof(registers) / sizeof(rcode_t); 
    int i;

    for (i = 0; i < op_count; i++) {
        if (strcmp(operations[i].op_str, word) == 0) {
            return i + 1;
        }
    }

    for (i = 0; i < reg_count; i++) {
        if (strcmp(registers[i].name, word) == 0) {
            return i + 1;
        }
    }

    return atoi(word);
}
