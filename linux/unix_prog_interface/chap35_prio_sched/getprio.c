/*!
 * 获取priority
 * int getpriority(int which, id_t who);
 * int setpriority(int which , id_t who, int prio);
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h> //getpriority setpriority
#include <stdlib.h>
#include <errno.h>

static int id;

/*!特别需要注意getpriority返回<0是合法的，需要通过errno来读取*/
#define SHOWPRIO(which) \
    do { int lasterr=errno, s; \
        errno=0; \
        s =  getpriority(which, id); \
        if(errno) {\
            perror("getpriority"); \
            exit(1); \
        } else {\
            errno = lasterr; \
        }\
        printf("pid=%d, %s: %d.\n", id ? id : getpid(),#which, s) ; } while(0)

int 
main(int argc, char *argv[]) {
    int i;
    char *endptr;
    for(i=0; i<argc; ++i) {
        if(i == 0) {
            id = 0;
        } else {
            id = strtol(argv[i], &endptr, 0);
            if(id <= 0) continue;
        }

        SHOWPRIO(PRIO_PROCESS);
        SHOWPRIO(PRIO_PGRP);
        SHOWPRIO(PRIO_USER);
        printf("\n");
    }
    return 0;
}

