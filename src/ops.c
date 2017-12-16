#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
    {0, "nop", nop},
    
    // MATH =============
    {2, "add", vadd},
    {2, "sub", vsub},
    {2, "mul", vmul},
    {2, "div", vdiv},
    {2, "mod", vmod},
    // ==================

    // COMPARISON =======
    {2, "eq", eq},
    {2, "neq", neq},
    {2, "lt", lt},
    {2, "lte", lte},
    {2, "gt", gt},
    {2, "gte", gte},
    // ==================

    // MOVE =============
    {2, "mv", mv},
    // ==================

    // BRANCH ===========
    {1, "hop", hop},
    {1, "hopt", hopt},
    {1, "hopf", hopf},
    // ==================

    // PRINT ============
    {1, "print", print},
    {1, "printn", printn},
    // ==================

    // STACK ============
    {1, "push", push},
    {1, "pop", pop},
    // ==================

    // ROUTINES =========
    {1, "call", call},
    {0, "ret", ret},
    // ==================

    {0, "exit", vexit},

    {0, NULL, NULL}
};

op_t *is_instruction(char *word) {
    int i = 0;

    while (operations[i].op_str && strcmp(operations[i].op_str, word) != 0)
        i++;

    return (operations[i].op_str) ? &operations[i] : NULL;
}
