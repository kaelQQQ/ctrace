#ifndef CT_TYPES_H
#define CT_TYPES_H
#include <sys/types.h>
#include <unistd.h>
#include "macros.h"
#include "arch/x86/types.i"
typedef struct{
    pid_t pid;
    unsigned int cost;
    int ret;
    k_ulong_t syscall;
    k_ulong_t regs[REG_NUM_MAX];
    char syscall_mask[SYSCALL_MASK_SIZE];
}tinfo;

#define BYTE_SIZE 8
#define HIT_SYSCALL_MASK(ti) \
    ti->syscall_mask[(ti->syscall)/BYTE_SIZE] & (1 << (ti->syscall%BYTE_SIZE)) 

#define SET__SYSCALL_MASK(ti, m) \
    ti->syscall_mask[(m)/BYTE_SIZE] |= (1 << ((m)%BYTE_SIZE))




typedef enum {
    SC_IN,
    SC_OUT
} SC_DIR;

#endif
