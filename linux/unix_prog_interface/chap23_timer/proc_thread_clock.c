/*!
 * 获取进程或线程的cpu运行时间，主要api
 * int clock_getcpuclockid(pid_t pid, clockid_t* cid);
 * int pthread_getcpuclockid(pthread_t thread, clockid_t* cid);
 *
 * return:0 success，否则失败
 *
 * int clock_gettime(clockid_t cid, struct timespec* ts);
 * int clock_settime(clockid_t cid, struct timespec* ts);
 *
 * 特别注意clockid_t并不是一个固定的枚举值，也可能会是一个组合值
    PRINT(CLOCK_REALTIME);
    PRINT(CLOCK_MONOTONIC);
    PRINT(CLOCK_PROCESS_CPUTIME_ID);
    PRINT(CLOCK_THREAD_CPUTIME_ID);
*
*/

#include <stdio.h>
#include <time.h> //clock_getcpuclockid
#include <pthread.h> //pthread_getcpuclockid
#include <stdlib.h>
#include <memory.h>

#define PRINT(x) \
    do { printf(#x"=%d\n",x); } while(0)

void
printTimeSpec(struct timespec* ts, const char *s) {
    printf("%s: %lds, %ldms\n", s, ts->tv_sec, ts->tv_nsec/(1000*1000));
}

int
main(int argc, char *argv[]) {
    pid_t pid;
    clockid_t cid;
    char buf[64];
    struct timespec ts;

    if(argc != 2) {
        printf("%s <pid> \n", argv[0]);
        return 1;
    }

    pid = atoi(argv[1]);
    if(clock_getcpuclockid(pid, &cid)) {
        perror("clock_getcpuclockid");
        return 1;
    }

    if(clock_gettime(cid, &ts)) {
        perror("clock_gettime");
        return 1;
    }

    PRINT(cid);
    PRINT(CLOCK_REALTIME);
    PRINT(CLOCK_MONOTONIC);
    PRINT(CLOCK_PROCESS_CPUTIME_ID);
    PRINT(CLOCK_THREAD_CPUTIME_ID);

    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf),"pid=%d", pid);
    printTimeSpec(&ts, buf);

    return 0;
}

