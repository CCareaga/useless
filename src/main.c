#include "vm.h"
#include "interpreter.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    int debug = 0;
    int c;

    while ((c = getopt (argc, argv, "d")) != -1) {
        switch (c) {
            case 'd':
                debug = 1;
                break;

            default:
                abort();
        }
    }
    
    char **files = argv + optind;

    executable_t *exec = vm_load(files, debug);

    // NOTE: assembler.c is currently unused but it is possible to save useless 
    // programs as binary files and read them into an exec struct using these lines
    // executable_t *exec = read_bin(argv[1]);
    // if (!exec) return -1;

    vm_execute(exec);
    vm_unload(exec);
}   

