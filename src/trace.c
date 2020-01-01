#include <stdio.h>
#include <syscall.h>
#include <sys/ptrace.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "trace.h"
#include "syscall_args.h"

#define TM_S_2_US(s) (s) * 1000000
#define TM_US_2_MS(us) (us) / 1000

static int _syscall_once(tinfo* ti) {
    if (ptrace(PTRACE_SYSCALL, ti->pid, 0, 0) == -1) {
            return -1;
    } 
    if (waitpid(ti->pid, 0, 0) == -1) {
        return -1;
    }
    return 0;
}

static int _syscall_in(tinfo* ti) {

    if (_syscall_once(ti) == -1) {
        return -1;
    }
    struct user_regs_struct regs;
    if (ptrace(PTRACE_GETREGS, ti->pid, 0, &regs) == -1) {
        return -1;
    }

    get_syscall_args(ti, &regs);
    return 0;
}

static int _syscall_out(tinfo* ti) {
    if (_syscall_once(ti) == -1) {
        return -1;
    }
    struct user_regs_struct regs;
    if (ptrace(PTRACE_GETREGS, ti->pid, 0, &regs) == -1) {
        return -1;
    }
    get_syscall_ret(ti, &regs);
    return 0;
}



tinfo* ct_attach_proc(pid_t pid) {
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
        tinfo* ti = (tinfo*)malloc(sizeof(tinfo));
        ti->pid = pid;
        for (int i = 0; i < sizeof(ti->syscall_mask); ++i) {
            ti->syscall_mask[i] = 0xff;
        }
        return ti;
    } while(0);
    return NULL;
}


int ct_syscall_next(tinfo* ti) {

    while(1) {
        struct timeval in, out;
        if (_syscall_in(ti) == -1) {
            return -1;
        }
        gettimeofday (&in, NULL);

        if (_syscall_out(ti) == -1) {
            return -1;
        }
        gettimeofday (&out, NULL);
        ti->cost = TM_US_2_MS(TM_S_2_US(out.tv_sec - in.tv_sec) + out.tv_usec - in.tv_usec);
        if (HIT_SYSCALL_MASK(ti)) {
            break;
        }
    }

    if (ti->syscall == 1) {
        print_syscall(1, ti, SC_OUT);
    }    
    return 0;
}

int ct_detach_proc(tinfo* ti) {
    if (ti) {
        ptrace(PTRACE_DETACH, ti->pid, 0, 0);
        free(ti);
    }
    //detach pid?
}
