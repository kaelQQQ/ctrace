#ifndef CT_TYPES_H
#define CT_TYPES_H
#include <sys/types.h>
#include <unistd.h>

#include "arch/x86/types.i"
typedef struct{
    pid_t pid;
    unsigned int cost;
    k_ulong_t ret;
    k_ulong_t syscall;
    k_ulong_t regs[REG_NUM_MAX];

}ctinfo;

typedef enum {
    SC_IN,
    SC_OUT
} SC_DIR;

#endif
