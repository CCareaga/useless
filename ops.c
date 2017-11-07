#include <string.h>
#include <stdlib.h>
    
#include "ops.h"
#include "vm.h"

op_t operations[] = {
    {0, "NOP", nop},
    // MATH
    {2, "ADDR", addr},
    {2, "SUBR", subr},
    {2, "MULR", mulr},
    {2, "DIVR", divr},
    {2, "MODR", modr},
    {2, "ADDL", addl},
    {2, "SUBL", subl},
    {2, "MULL", mull},
    {2, "DIVL", divl},
    {2, "MODL", modr},
    {2, "ADDLR", addlr},
    {2, "SUBLR", sublr},
    {2, "MULLR", mullr},
    {2, "DIVLR", divlr},
    {2, "MODLR", modlr},
    {2, "ADDRL", addrl},
    {2, "SUBRL", subrl},
    {2, "MULRL", mulrl},
    {2, "DIVRL", divrl},
    {2, "MODRL", modrl},

    // COMPARISON
    {2, "EQR", eqr},
    {2, "NEQR", neqr},
    {2, "LTR", ltr},
    {2, "LTER", lter},
    {2, "GTR", gtr},
    {2, "GTER", gter},

    {2, "EQL", eql},
    {2, "NEQL", neql},
    {2, "LTL", ltl},
    {2, "LTEL", ltel},
    {2, "GTL", gtl},
    {2, "GTEL", gtel},

    {2, "EQLR", eqlr},
    {2, "NEQLR", neqlr},
    {2, "LTLR", ltlr},
    {2, "LTELR", ltelr},
    {2, "GTLR", gtlr},
    {2, "GTELR", gtelr},

    // STORAGE, MOVE, DEREFERNCE
    {2, "STORR", storr},
    {2, "STORL", storl},

    {2, "MVRL", mvrl},
    {2, "MVLR", mvlr},
    {2, "MVRR", mvrr},
    {2, "MVLL", mvll},

    {2, "DREFR", drefr},
    {2, "DREFL", drefl},

    // BRANCH
    {1, "LHOP", lhop},
    {1, "LHOPT", lhopt},
    {1, "LHOPF", lhopf},

    // PRINT
    {1, "PRINTR", printr},
    {1, "PRINTL", printl},

    // STACK
    {1, "PUSH", push},
    {1, "PUSHR", pushr},
    {1, "PUSHL", pushl},
    {0, "POP", pop},
    {1, "POPR", popr},
    {1, "POPL", popl},
    {0, "EXIT", vexit}
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
