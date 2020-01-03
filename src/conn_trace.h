#ifndef CT_CONN_TRACE_H
#define CT_CONN_TRACE_H

#include "trace.h"
#include <sys/types.h>
#include <sys/socket.h>
typedef struct {
    tinfo ti;
    struct sockaddr addr
}conninfo;


conninfo* conn_attach_proc(pid_t pid);
int conn_syscall_next(conninfo* ti);

#endif