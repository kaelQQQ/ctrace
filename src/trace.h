#ifndef CT_TRACE_H
#define  CT_TRACE_H
#include <sys/types.h>
#include <unistd.h>
#include "types.h"


tinfo* t_attach_proc(pid_t pid);
int t_syscall_next(tinfo* ti);
int t_syscall_in(tinfo* ti);
int t_syscall_out(tinfo* ti);
int t_detach_proc(tinfo* ti);
#endif