#include<stdio.h>
#include <string.h>
#include <errno.h>
#include"ctrace.h"

int main(int argc, char * argv[]) {

                if (argc < 2) {
                        printf("miss pid\n");
                }
        ctinfo *ci = ct_attach_proc(atoi(argv[1]));
        int ret = 0;
        if (ci == NULL) {
                printf(strerror(errno));
                return;
        }
        while(1) {
                ret = ct_syscall_next(ci);
                if (ret) {
                        printf(strerror(errno));
                }
        }
}