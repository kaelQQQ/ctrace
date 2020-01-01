#ifndef CT_SYSCALL_ARGS_H
#define CT_SYSCALL_ARGS_H

#include <sys/user.h>
#include "types.h"
typedef int(*ArgPrint)(ctinfo* ci, SC_DIR dir);
void get_syscall_ret(ctinfo *ci, struct user_regs_struct *regs);
void get_syscall_args(ctinfo *ci, struct user_regs_struct *regs);
int print_syscall(int syscall, ctinfo* ci, SC_DIR dir);
#endif