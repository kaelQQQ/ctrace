#include <stdio.h>
#include "syscall_args.h"
#include "arch/x86/syscall_arg.i"

int p_read(ctinfo* ci, SC_DIR dir) {
    if (dir == SC_IN) {
        printf("this is read in\n");
    } else
    {
         printf("this is read out\n");
    }
    
    return 0;
}


int p_write(ctinfo* ci, SC_DIR dir) {
    if (dir == SC_IN) {
        printf("this is write in\n");
    } else
    {
         printf("this is write out\n");
    }
    
    return 0;
}


int print_syscall(int syscall, ctinfo* ci, SC_DIR dir) {
    if (syscall == 0 ) {
        return p_read(ci, dir);
    }

    return p_write(ci, dir);
}
