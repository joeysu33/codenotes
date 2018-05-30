/*!
 * 设置进程/进程组/用户的priority
 * -20 ~ 19
 */

#include <unistd.h>
#include <sched.h>
#include <sys/resource.h> //getpriority setpriority
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h> //strcasecmp strncasecmp
#include <string.h>

int 
main(int argc, char *argv[]) {
    char *endptr;
    int pid, prio, which;

    if(argc != 4) {
        fprintf(stderr, "%s: <pid> <type(proc|pg|user)> <priority>.\n", argv[0]);
        return 1;
    }

    pid = strtol(argv[1], &endptr, 0);
    prio = strtol(argv[3], &endptr, 0);
    if(strcasecmp(argv[2], "proc") == 0) {
        which = PRIO_PROCESS;
    } else if(strcasecmp(argv[2], "pg") == 0) {
        which = PRIO_PGRP;
    } else {
        which = PRIO_USER;
    }

    return 0;
}
