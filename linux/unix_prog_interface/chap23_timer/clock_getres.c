/*!
 * 获取当前的时钟分辨率
 */

#include <sys/time.h>
#include <time.h>
#include <stdio.h>

void
printTimeSpec(struct timespec* ts, const char *s) {
    printf("%s: %lds, %ldns\n", s, ts->tv_sec, ts->tv_nsec);
}

int 
main() {
    int i;
    clockid_t clks[] = { CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID };
    char* clksName[] = { "CLOCK_REALTIME", "CLOCK_MONOTONIC", "CLOCK_PROCESS_CPUTIME_ID", "CLOCK_THREAD_CPUTIME_ID" };
    struct timespec ts;

    /*!Posix API ==0:success !=0 faliure*/
    for(i= sizeof(clks)/sizeof(int) -1; i; --i) {
        if(clock_getres(i, &ts)) {
            perror("clock_getres ");
            return 1;
        }
        printTimeSpec(&ts, clksName[i]);
    }

    return 0;
}

