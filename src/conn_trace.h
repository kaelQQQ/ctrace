#ifndef CT_CONN_TRACE_H
#define CT_CONN_TRACE_H

#include "trace.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
typedef struct {
    tinfo *ti;
    struct sockaddr_in addr;
} conninfo;


conninfo* conn_attach_proc(pid_t pid);
int conn_syscall_next(conninfo* ti);
int conn_detach_proc(conninfo* ci);
#endif
