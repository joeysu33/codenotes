/*!
 * 获取线程CPU消耗的时间
 * int pthread_getcpuclockid(pthread_t tid, clockid_t *clockid);
 * int clock_gettime(clockid_t clockid, struct timespec *tp);
 */

#include <unistd.h>
#include <time.h> //clock_*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define handle_error(s, what) \
    do {errno = s; perror(what); exit(1);} while(0)

void
showTimeSpec(struct timespec* tp) {
    printf("seconds:%lds, nanoseconds:%lds.\n",
            tp->tv_sec, tp->tv_nsec);
}

void*
threadFunc(void* arg) {
    sleep(3);
    return NULL;
}

int
main(int argc, char *argv[]) {
    clockid_t clock;
    struct timespec tp;
    int s;
    pthread_t tid;

    s = pthread_create(&tid, NULL, threadFunc, NULL);
    if(s) handle_error(s, "pthread_create");
    
    sleep(1);
    if(pthread_getcpuclockid(tid, &clock) < 0) {
        perror("clock_getcpuclockid");
        return 1;
    }
    if(clock_gettime(clock, &tp) < 0) {
        perror("clock_gettime");
        return 1;
    }
    printf("TID=%ld : Running for ",tid);
    showTimeSpec(&tp);
    pthread_join(tid,NULL);

    printf("After thread finish!\n");
    if(pthread_getcpuclockid(tid, &clock) < 0) {
        perror("clock_getcpuclockid");
        return 1;
    }
    if(clock_gettime(clock, &tp) < 0) {
        perror("clock_gettime");
        return 1;
    }
    printf("TID=%ld : Running for ",tid);
    showTimeSpec(&tp);

    return 0;
}

