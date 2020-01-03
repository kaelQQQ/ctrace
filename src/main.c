#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "conn_trace.h"

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("miss pid\n");
    }
    conninfo *ti = conn_attach_proc(atoi(argv[1]));
    int ret = 0;
    if (ti == NULL) {
        printf(strerror(errno));
        return 0;
    }
    while(1) {
        ret = conn_syscall_next(ti);
        if (ret) {
            printf(strerror(errno));
        }
    }
todo:
    conn_detach_proc(ti);
    return 0;
}
