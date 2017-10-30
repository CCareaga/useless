#include "vm.h"
#include "interpreter.h"

int main() {
    executable_t *exec = vm_load("bin/test.ass");
    vm_execute(exec);
    vm_unload(exec);
}   
