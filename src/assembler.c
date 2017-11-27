#include <stdio.h>

#include "interpreter.h"
    
void write_header(executable_t *exec, FILE *fp) {
    int magic = 0xd00ddead;

    fwrite(&magic, sizeof(int), 1, fp);
    fwrite(&exec->length, sizeof(int), 1, fp);
    fwrite(&exec->entry, sizeof(int), 1, fp);
}

int exec_to_bin(executable_t *exec, char *fn) {
    FILE *fp = fopen (fn, "wb");  
    if (!fp) return -1;

    write_header(exec, fp); 
    fwrite(exec->code, sizeof(int), exec->length, fp);

    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    
    executable_t *exec = vm_load(&argv[2]);
    exec_to_bin(exec, argv[1]);

    return 0;
}

