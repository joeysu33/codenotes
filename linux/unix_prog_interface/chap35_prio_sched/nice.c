/*!
 * 实现和系统工具nice一样的工具
 * 可以设置可执行程序的nice值
 *
 * 因为nice值是自动继承，所以可以在execve之前设置好
 * ajdust 默认值是0
 * nice -n ? cmd argv
 */


#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>  //system, strtol
#include <strings.h> //strcasecmp
#include <string.h>

#include <sys/time.h>
#include <sys/resource.h> //setpriority

void
showArguments(int argc, char* argv[]) {
    int counter;
    char **arg;
    for(arg = &argv[0], counter=0; *arg; arg++, counter++) {
        printf("arg[%d]=%s\n", counter, *arg);
    }
}

int
main(int argc, char *argv[]) {
    int prio;
    int i, j;
    char *endptr;

    showArguments(argc, argv);
    /*!检测system是否可用, ":"空命令*/
    if(system(":") < 0) {
        perror("system()");
        return 1;
    }

    if(argc < 4) {
        fprintf(stderr, "Usage: %s -n <piro> <command> <args>.\n", argv[0]);
        return 1;
    }
    
    if(strcmp(argv[1], "-n")) {
        fprintf(stderr, "Mandatory [-n] is not set!\n");
        return 1;
    }
    prio = strtol(argv[2], &endptr, 0);
    if(prio < 0 || prio > 20) {
        fprintf(stderr, "priority should be [0,20]");
        return 1;
    }
    setpriority(PRIO_PROCESS, 0, prio);

    /*
    switch(fork()) {
        case -1: return 1;
        case 0: break;
        default: return 0;
    }*/

    /*! first argument is argv[0] */
    execvp(argv[3], &argv[3]);
    perror("execvp");
    return 1;
}


