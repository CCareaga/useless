#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
    {0, "NOP", nop},
    
    // MATH ==============
    {2, "ADD", vadd},
    {2, "SUB", vsub},
    {2, "MUL", vmul},
    {2, "DIV", vdiv},
    {2, "MOD", vmod},
    // ===================

    // COMPARISON ========
    {2, "EQ", eq},
    {2, "NEQ", neq},
    {2, "LT", lt},
    {2, "LTE", lte},
    {2, "GT", gt},
    {2, "GTE", gte},
    // ==================

    // STORAGE, MOVE, DEREFERNCE
    {2, "MV", mv},
    {1, "DREF", dref},
    // ==================

    // BRANCH ===========
    {1, "HOP", hop},
    {1, "HOPT", hopt},
    {1, "HOPF", hopf},
    // ==================

    // PRINT ============
    {1, "PRINT", print},
    // ==================

    // STACK ============
    {1, "PUSH", push},
    {1, "POP", pop},
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
