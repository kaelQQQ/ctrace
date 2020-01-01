#ifndef CT_CTRACE_H
#define  CT_CTRACE_H
#include <sys/types.h>
#include <unistd.h>
#include "types.h"


ctinfo* ct_attach_proc(pid_t pid);
int ct_syscall_next(ctinfo* ci);
int ct_syscall_in(ctinfo* ci);
int ct_syscall_out(ctinfo* ci);
int ct_detach_proc(ctinfo* ci);
#endif