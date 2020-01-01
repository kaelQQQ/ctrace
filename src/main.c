#include<stdio.h>
#include <string.h>
#include <errno.h>
#include"trace.h"

int main(int argc, char * argv[]) {

    if (argc < 2) {
        printf("miss pid\n");
    }
    tinfo *ti = ct_attach_proc(atoi(argv[1]));
    int ret = 0;
    if (ti == NULL) {
        printf(strerror(errno));
        return;
    }
    while(1) {
        ret = ct_syscall_next(ti);
        if (ret) {
            printf(strerror(errno));
        }
    }
}