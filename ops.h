#ifndef _OPS_H
#define _OPS_H

typedef struct {
    int argc;           // arg count
    const char *op_str; // operation name
} op_t;

typedef struct {
    const char *name;   // register name
} rcode_t;

enum {
    NOP,
    ADD,
    SUB,
    EXIT,
    LOAD,
    STORE,
    LHOP,
    LHOPT,
    PRINTR,
    EQ,
};

int get_opcode(char *word);

#endif // _OPS_H
