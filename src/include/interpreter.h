#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <stddef.h>

// linked list node for the label list, each one represents a label
// in the currently running program, only used for byte-code conversion
typedef struct lnode_t {
    char *name;
    int address;
    struct lnode_t *next;
} lnode_t;

// linked list node for the line number information list, there one of these for
// each line in the program. each node stores the range of addresses on a given
// line. this list is only used for the debugger to set break points
typedef struct lnum_t {
    char *fname;
    int num;
    int start;
    struct lnum_t *next;
} lnum_t;

typedef struct {
    size_t length;          // length of the executable
    int *code;              // array of op codes
    int entry;              // entry point of the program
    struct lnode_t *labels; // label table
    struct lnum_t *lnums;   // line num table
} executable_t;

executable_t *vm_load(char **fn);
void vm_unload(executable_t *e);
int is_label(executable_t *exec, char *word);

#endif
