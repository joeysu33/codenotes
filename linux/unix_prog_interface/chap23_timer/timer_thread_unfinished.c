/*!
 * 通过线程来处理timer定时器
 * 主要需要设置struct sigenv*
 * 每次通知都会创建一个线程
 */

#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/time.h>

static int expireCount ;
static pthread_mutex_t pmt;
static pthread_cond_t  pct;

void 
threadFunc(union sigval val) {
}


int 
main() {
    struct sigevent sev;
    struct itimerspec its;
    int i, j;
    timer_t tids [2];

    memset(&sev, 0, sizeof(sev));
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = threadFunc;
    sev.sigev_notify_attributes = NULL;

    /*!初始化*/
    pthread_mutex_init(&pmt, NULL);
    pthread_cond_init(&pct, NULL);

    sev.sigev_value.sival_int = 100;
    if(timer_create(CLOCK_REALTIME, &sev, &tids[0]) != 0) {
        perror("timer_create ");
        return 1;
    }

    sev.sigev_value.sival_int = 200;
    if(timer_create(CLOCK_REALTIME, &sev, &tids[1]) != 0) {
        perror("timer_create ");
        return 1;
    }

    printf("tids[0]=%p, tids[1]=%p\n", tids[0], tids[1]);

    memset(&its, 0, sizeof(its));
    its.it_interval.tv_sec = 2;
    its.it_interval.tv_nsec = 1000*10;
    if(timer_settime(tids[0], 0, &its, NULL) != 0) {
        perror("timer_settime ");
        return 1;
    }

    its.it_interval.tv_sec = 5;
    its.it_interval.tv_nsec = 1000;
    its.it_value.tv_sec = 4;
    if(timer_settime(tids[1], 0, &its, NULL) != 0) {
        perror("timer_settime");
        return 1;
    }

    for(;;) {
        pthread_cond_wait(&pct, &pmt);
    }

    return 0;
}

