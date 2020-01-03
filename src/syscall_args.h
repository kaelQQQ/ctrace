#ifndef CT_SYSCALL_ARGS_H
#define CT_SYSCALL_ARGS_H

#include <sys/user.h>
#include "types.h"
typedef int(*ArgPrint)(tinfo* ti, SC_DIR dir);
void get_syscall_ret(tinfo *ti, struct user_regs_struct *regs);
void get_syscall_args(tinfo *ti, struct user_regs_struct *regs);
int print_syscall(int syscall, tinfo* ti, SC_DIR dir);
static int peekdata(const int pid, k_ulong_t addr, k_ulong_t len, void *buff);
#endif