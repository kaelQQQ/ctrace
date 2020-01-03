#include <stdio.h>
#include <sys/ptrace.h>
#include <string.h>
#include <errno.h>

#include "macros.h"
#include "syscall_args.h"
#include "arch/x86/syscall_arg.i"


int peekdata(const int pid, k_ulong_t addr, k_ulong_t len, void *buff)
{
    unsigned int residue = addr & (sizeof(long) - 1);
    while (len) {
        addr &= -sizeof(long);          /* aligned address */
        union {
            long val;
            char x[sizeof(long)];
        } u = { .val = ptrace(PTRACE_PEEKDATA, pid, addr, 0) };
        if (errno) {
            return -1;
        }
        k_ulong_t m = MIN(sizeof(long) - residue, len);
        memcpy(buff, &u.x[residue], m);
        residue = 0;
        addr += sizeof(long);
        buff += m;
        len -= m;
    }
    return 0;
}

int p_read(tinfo* ti, SC_DIR dir) {
    if (dir == SC_IN) {
        printf("this is read in\n");
    } else
    {
         printf("this is read out\n");
    }
    
    return 0;
}


int p_write(tinfo* ti, SC_DIR dir) {
    if (dir == SC_IN) {
        printf("this is write in\n");
    } else
    {
         printf("this is write out\n");
    }
        char buff[1024] = {0};
        peekdata(ti->pid, ti->regs[1], ti->regs[2], buff);
    printf(buff);
    return 0;
}


int print_syscall(int syscall, tinfo* ti, SC_DIR dir) {
    if (syscall == 0 ) {
        return p_read(ti, dir);
    }

    return p_write(ti, dir);
}



