/*!
 * 获取进程CPU消耗的时间,clockid_t隐含了进程/线程的信息
 *
 * int clock_getcpuclockid(pid_t pid, clockid_t *clockid);
 * int clock_gettime(clockid_t clockid, struct timespec *tp);
 */

#include <unistd.h>
#include <time.h> //clock_*
#include <stdio.h>
#include <stdlib.h>

void
showTimeSpec(struct timespec* tp) {
    printf("seconds:%lds, nanoseconds:%lds.\n",
            tp->tv_sec, tp->tv_nsec);
}
int
main(int argc, char *argv[]) {
    pid_t pid;
    char *endptr;
    clockid_t clock;
    struct timespec tp;

    if(argc != 2) {
        fprintf(stderr, "%s: <pid>.\n", argv[0]);
        return 1;
    }

    pid = strtol(argv[1], &endptr, 0);
    if(pid <= 0) {
        fprintf(stderr, "Invalid pid value.\n");
        return 1;
    }

    if(clock_getcpuclockid(pid, &clock) < 0) {
        perror("clock_getcpuclockid");
        return 1;
    }
    if(clock_gettime(clock, &tp) < 0) {
        perror("clock_gettime");
        return 1;
    }
    printf("PID=%d : Running for ",pid);
    showTimeSpec(&tp);

    return 0;
}

