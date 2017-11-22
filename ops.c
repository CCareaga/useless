#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
    {0, "NOP", nop},
    
    // MATH ==============

    // vanilla
    {2, "ADD", NULL},
    {2, "SUB", NULL},
    {2, "MUL", NULL},
    {2, "DIV", NULL},
    {2, "MOD", NULL},
    // ===================

    // COMPARISON ========

    // vanilla
    {2, "EQ", NULL},
    {2, "NEQ", NULL},
    {2, "LT", NULL},
    {2, "LTE", NULL},
    {2, "GT", NULL},
    {2, "GTE", NULL},
    // ==================

    // STORAGE, MOVE, DEREFERNCE
    {2, "MV", mv},

    {2, "DREF", dref},
    // ==================

    // BRANCH ===========
    {1, "HOP", NULL},
    {1, "HOPT", NULL},
    {1, "HOPF", NULL},
    // ==================

    // PRINT ============
    {1, "PRINT", NULL},
    // ==================

    // STACK ============
    {1, "PUSH", NULL},
    {0, "POP", NULL},
    {0, "EXIT", vexit},
    // ==================
    {0, NULL, NULL}
};

op_t *is_instruction(char *word) {
    int i = 0;

    while (operations[i].op_str && strcmp(operations[i].op_str, word) != 0)
        i++;

    if (operations[i].op_str)
        return &operations[i];
    else 
        return NULL;
}

// searches through the arrays of operations and registers to determine
// the opcode for a given word. if no opcode is found via arrays, atoi is used
int get_opcode(const char *word) {
    int op_count  = sizeof(operations) / sizeof(op_t); 
    int i;

    for (i = 0; i < op_count; i++) {
        if (operations[i].op_str && strcmp(operations[i].op_str, word) == 0) {
            return i;
        }
    }

    return atoi(word);
}
