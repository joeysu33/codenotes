/*!
 * 获取priority
 * int getpriority(int which, id_t who);
 * int setpriority(int which , id_t who, int prio);
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h> //getpriority setpriority

#define SHOWPRIO(which) \
    do { printf("%s: %d.\n", #which, getpriority(which, 0)) ;} while(0)

int 
main() {
    SHOWPRIO(PRIO_PROCESS);
    SHOWPRIO(PRIO_PGRP);
    SHOWPRIO(PRIO_USER);

    return 0;
}

