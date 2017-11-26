#include "vm.h"
#include "interpreter.h"

int main(int argc, char **argv) {
    if (argc < 2) return 1;

    executable_t *exec = vm_load(&argv[1]);
    vm_execute(exec);
    vm_unload(exec);
}   
