#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/ptrace.h>
#include "conn_trace.h"
#include "syscall_args.h"

char tcp_mask[SYSCALL_MASK_SIZE] = { 0x00 };

conninfo* conn_attach_proc(pid_t pid) {
    tinfo *ti = t_attach_proc(pid);
    if (ti == NULL) {
        return NULL;
    }
    conninfo *ci = (conninfo *)malloc(sizeof(conninfo));
    if (ci == NULL) {
        return NULL;
    }
    ci->ti = ti;
    tcp_mask[5] = 0x04;
    memcpy(ci->ti->syscall_mask, tcp_mask, SYSCALL_MASK_SIZE);
    return ci;
}

int conn_syscall_next(conninfo* ci) {
    int ret = t_syscall_next(ci->ti);
    if (ret == -1) {
        return ret;
    } 
    ret = peekdata(ci->ti->pid, ci->ti->regs[1], ci->ti->regs[2], &ci->addr);
    if (ret == -1) {
        printf("err:%d  %s", errno, strerror(errno));
        return ret;
    }
    char buff[24] = {0};
    inet_ntop(AF_INET, &(ci->addr.sin_addr), buff, INET_ADDRSTRLEN);
    printf("syscall connect(%lu, ip:%s, port:%u) ret:%d, cost:%d\n",
        ci->ti->regs[0],buff, ntohs(ci->addr.sin_port),
        ci->ti->ret, ci->ti->cost);
    return 0;
}

int conn_detach_proc(conninfo* ci) {
    if (ci) {
        t_detach_proc(ci->ti);
        free(ci);
    }
    //detach pid?
}

