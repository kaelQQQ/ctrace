#include <stdio.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "ctrace.h"
#include "syscall_args.h"

#define TM_S_2_US(s) (s) * 1000000
#define TM_US_2_MS(us) (us) / 1000


ctinfo* ct_attach_proc(pid_t pid) {
    do {
        if (getpid() == pid || pid < 1) {
            break;
        }

        if (ptrace(PTRACE_ATTACH, pid, 0L, 0L) == -1) {
            break;
        }

        if (waitpid(pid, 0, 0) == -1) {
            break;
        }
        ctinfo* ci = (ctinfo*)malloc(sizeof(ctinfo));
        ci->pid = pid;
        return ci;
    } while(0);
    return NULL;
}

int _syscall_once(ctinfo* ci) {
    if (ptrace(PTRACE_SYSCALL, ci->pid, 0, 0) == -1) {
            return -1;
    } 
    if (waitpid(ci->pid, 0, 0) == -1) {
        return -1;
    }
    return 0;
}
int ct_syscall_in(ctinfo* ci) {

    if (_syscall_once(ci) == -1) {
        return -1;
    }
    struct user_regs_struct regs;
    if (ptrace(PTRACE_GETREGS, ci->pid, 0, &regs) == -1) {
        return -1;
    }

    get_syscall_args(ci, &regs);
    return 0;
}

int ct_syscall_out(ctinfo* ci) {
    if (_syscall_once(ci) == -1) {
        return -1;
    }
    struct user_regs_struct regs;
    if (ptrace(PTRACE_GETREGS, ci->pid, 0, &regs) == -1) {
        return -1;
    }
    get_syscall_ret(ci, &regs);
    return 0;
}


int ct_syscall_next(ctinfo* ci) {
    do {
        struct timeval in, out;
        if (ct_syscall_in(ci) == -1) {
            return -1;
        }
        gettimeofday (&in, NULL);

        if (ct_syscall_out(ci) == -1) {
            return -1;
        }
        gettimeofday (&out, NULL);
        ci->cost = TM_US_2_MS(TM_S_2_US(out.tv_sec - in.tv_sec) + out.tv_usec - in.tv_usec);
        //printf("syscall:%d, ret:%ld, cost: %d\n", ci->syscall, ci->ret, ci->cost);

        if (ci->syscall == 1) {
            print_syscall(1, ci, SC_OUT);
        }
        return 0;
    }while(0);
    return -1;
}

int ct_detach_proc(ctinfo* ci) {
    if (ci) {
        ptrace(PTRACE_DETACH, ci->pid, 0, 0);
        free(ci);
    }
    //detach pid?
}
