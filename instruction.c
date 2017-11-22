#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ops.h"
#include "vm.h"

#define ocode(o1, o2, o3, o4) ((o4 << 12) | (o3 << 8) | (o2 << 4) | o1)

int nop(cpu_t *cpu, int *ram, uint16_t type) {
    return 1;
}

int dref(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 
    printf("VAL = %d \n", val);
    ram[4] = ram[ram[val]];
    return 1;
}

int mv(cpu_t *cpu, int *ram, uint16_t type) {

    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] = val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] = ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] = ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] = val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] = ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] = ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

// MATH INSTRUCTIONS =============================
int vadd(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] += val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] += ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] += ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] += val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] += ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] += ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vsub(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] -= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] -= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] -= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] -= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] -= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] -= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vmul(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] *= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] *= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] *= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] *= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] *= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] *= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vdiv(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] /= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] /= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] /= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] /= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] /= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] /= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}

int vmod(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 
    
    switch (type) {
        case (ocode(L, M, 0, 0)):
            ram[val2] %= val1;
            break;

        case (ocode(R, M, 0, 0)):
            ram[val2] %= ram[ram[val1]];
            break;
        
        case (ocode(M, M, 0, 0)):
            ram[val2] %= ram[val1];
            break;

        case (ocode(L, R, 0, 0)):
            ram[ram[val2]] %= val1;
            break;

        case (ocode(M, R, 0, 0)):
            ram[ram[val2]] %= ram[val1];
            break;

        case (ocode(R, R, 0, 0)):
            ram[ram[val2]] %= ram[ram[val1]];
            break;

        default:
            return 0;
    }

    return 1;
}
// ===============================================

int eq(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] == val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] == ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] == ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] == val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] == ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] == ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int neq(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] != val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] != ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] != ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] != val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] != ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] != ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int lt(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] < val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] < ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] < ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] < val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] < ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] < ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int lte(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] <= val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] <= ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] <= ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] <= val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] <= ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] <= ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int gt(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] > val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] > ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] > ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] > val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] > ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] > ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int gte(cpu_t *cpu, int *ram, uint16_t type) {
    int val1 = ram[++cpu->pc]; 
    int val2 = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, M, 0, 0)):
            cpu->flg = (ram[val2] >= val1);
            break;

        case (ocode(M, M, 0, 0)):
            cpu->flg = (ram[val2] >= ram[val1]);
            break;

        case (ocode(R, M, 0, 0)):
            cpu->flg = (ram[val2] >= ram[ram[val1]]);
            break;
        
        case (ocode(L, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] >= val1);
            break;

        case (ocode(M, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] >= ram[val1]);
            break;

        case (ocode(R, R, 0, 0)):
            cpu->flg = (ram[ram[val2]] >= ram[ram[val1]]);
            break;

        default:
            return 0;
    }

    return 1;
}

int hopt(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 
    if (!cpu->flg) return 1;

    switch (type) {
        case (ocode(L, 0, 0, 0)):
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;

        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        
        default:
            return 0;
    }

    return 1;
}

int hopf(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 
    if (cpu->flg) return 1;

    switch (type) {
        case (ocode(L, 0, 0, 0)):
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;

        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        
        default:
            return 0;
    }

    return 1;
}

int hop(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, 0, 0, 0)):
        case (ocode(M, 0, 0, 0)):
            cpu->pc = val - 1;
            break;

        case (ocode(R, 0, 0, 0)):
            cpu->pc = ram[val] - 1;
            break;

        
        default:
            return 0;
    }

    return 1;
}

int print(cpu_t *cpu, int *ram, uint16_t type) {
    int val = ram[++cpu->pc]; 

    switch (type) {
        case (ocode(L, 0, 0, 0)):
            putchar(val);
            break;

        case (ocode(M, 0, 0, 0)):
            putchar(ram[val]);
            break;

        case (ocode(R, 0, 0, 0)):
            putchar(ram[ram[val]]);
            break;
        
        default:
            return 0;
    }

    return 1;
}

int vexit(cpu_t *cpu, int *ram, uint16_t type) {
    return 0;
}
