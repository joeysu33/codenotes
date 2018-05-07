/*!
 * 验证程序
 * 调用timer_create，将evp设置为NULL指针，不给struct sigevent设置行为
 * 则，sigev_notify将设置为SIGEV_SIGNAL，默认通过信号来传递
 * sigev_signo将设置为SIGALRM，
 * 并且sigev_value.sival_int 设置为timerid
 */

#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <string.h> //strsignal
#include <errno.h>
#include <memory.h>

void
showTime(const char* s) {
    printf("%s: UTC:%lu\n", s, time(NULL));
}

void
sigaction_handler(int sig, siginfo_t *si, void* ucontext) {
    /*! Unsafe in async IO*/
    printf("signo:%d, strsigno:%s, si->si_value.sival_int=%d\n", si->si_signo, 
            strsignal(si->si_signo),
            si->si_value.sival_int);
    /*! Unsafe */
    showTime("signal-come");
}

int main() {
    struct sigaction sa;
    struct itimerspec its;
    int i;
    timer_t timerid;

    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; //sigaction_handler
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGALRM, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    /*!将timer的行为设置为默认值 sigevent为NULL */
    if(timer_create(CLOCK_REALTIME, NULL, &timerid) < 0) {
        perror("timer_create ");
        return 1;
    }

    printf("timerid=%lu\n", (unsigned long)timerid);
    showTime("Initialize");
    memset(&its, 0, sizeof(its));
    its.it_interval.tv_sec = 2;
    its.it_interval.tv_nsec = 1000 *1000 *500;
    its.it_value.tv_sec = 4;
    if(timer_settime(timerid, 0, &its, NULL) < 0) {
        perror("timer_settime");
        return 1;
    }

    /*!等待信号*/
    for(;;) pause();

    return 0;
}
