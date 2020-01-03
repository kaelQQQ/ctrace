#include <string.h>
#include <errno.h>
#include "conn_trace.h"
#include "syscall_args.h"

char tcp_mask[SYSCALL_MASK_SIZE] = { 0x00 }

tinfo* tcp_attach_proc(pid_t pid) {
    tinfo *ti = t_attach_proc(pid);
    if (ti == NULL) {
        return NULL;
    }

    tcp_mask[5] = 0x02;
    memcpy(ti->syscall_mask, tcp_mask, SYSCALL_MASK_SIZE);
    return ti;
}

int conn_syscall_next(conninfo* ci) {
    int ret = t_syscall_next((tinfo*)ci);
    if (ret == -1) {
        return ret;
    } 
    ret = peekdata(ci->ti->pid, ci->ti->regs[1], ci->ti->regs[2], &ci->addr)
    if (ret == -1) {
        printf("err:%d  %s", errno, strerror(errno));
        return ret;
    }
}