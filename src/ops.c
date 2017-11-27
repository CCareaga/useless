#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
    {0, "NOP", nop},
    
    // MATH =============
    {2, "ADD", vadd},
    {2, "SUB", vsub},
    {2, "MUL", vmul},
    {2, "DIV", vdiv},
    {2, "MOD", vmod},
    // ==================

    // COMPARISON =======
    {2, "EQ", eq},
    {2, "NEQ", neq},
    {2, "LT", lt},
    {2, "LTE", lte},
    {2, "GT", gt},
    {2, "GTE", gte},
    // ==================

    // MOVE =============
    {2, "MV", mv},
    // ==================

    // BRANCH ===========
    {1, "HOP", hop},
    {1, "HOPT", hopt},
    {1, "HOPF", hopf},
    // ==================

    // PRINT ============
    {1, "PRINT", print},
    {1, "PRINTN", printn},
    // ==================

    // STACK ============
    {1, "PUSH", push},
    {1, "POP", pop},
    // ==================

    // ROUTINES =========
    
    {1, "CALL", call},
    {0, "RET", ret},
    // ==================

    {0, "EXIT", vexit},

    {0, NULL, NULL}
};

op_t *is_instruction(char *word) {
    int i = 0;

    while (operations[i].op_str && strcmp(operations[i].op_str, word) != 0)
        i++;

    return (operations[i].op_str) ? &operations[i] : NULL;
}
