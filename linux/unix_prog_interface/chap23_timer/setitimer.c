/*!
 * unix上设置定时器的两种主要方式,这两种方式均是通过信号来实现，如果该定时器的通知信号
 * 程序不予捕获处理的话，会导致程序退出
 * SIGALRM: 响铃信号
 * SIGVTALRM: 进程用户时间响铃信号
 * SIGPROF: 进程时间(包含用户和系统)响铃信号
 * 1.系统API,特点，对每一种类型的只能是设置一个定时器
 *   1.setitimer getitimer
 *   2.alarm
 *   int setitimer(int which, struct itimerval *cur_val);
 *   int setitimer(int which, struct itimerval *cur_val, struct itimerval* old_val);
 *   struct itimeval {
 *      struct timeval it_interval; //间隔
 *      struct timeval it_value;    //下一次触发的事件
 *   };
 *
 *   struct timeval {
 *      int tv_sec;
 *      int tv_usec; // 不能大于1000 * 1000 
 *   }
 *   int which:
 *   ITIMER_REAL: 真实事件，和系统的时间直接有关系，time() ，触发SIGALRM信号
 *   ITIMER_VIRTUAL: 虚拟时间，进程执行中的用户时间, times()，触发SIGVTALRM信号
 *   ITIMER_PROF: 总体时间，进程执行过程中用户时间和系统时间的总和，触发SIGVTPROF信号
 *   return: -1 failed, 0 success
 *
 *   int alarm(int seconds);
 *   int seconds: 设置多少秒以后开始信号通知
 *   return 返回之前设置的定时器距离下次定时器通知的时间
 *   关闭alarm定时器 alarm(0)
 *
 * 2.Posix API
 *
 * 3.IO复用器, select,pselect,poll,ppoll, epoll
 */

#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <memory.h>
#include <time.h>

#include <sys/time.h> //setitimer

void
sigaction_handler(int sig, siginfo_t* si, void* uncontext) {
    /*! Unsafe in async IO*/
    printf("signal:%d, info:%s, time:%ld\n", sig, strsignal(sig), time(NULL));
    /*
    switch(sig) {
        case SIGALRM: {
                          break;
                      }
        case SIGVTALRM: {
                            break;
                        }
        case SIGPROF: {
                          break;
                      }

    }*/
}

/*!
 * 0.01s
 */
void 
elaspedTime() {
    int c = clock();
    for(;(clock() -c ) < (CLOCKS_PER_SEC /100);) ;
}

void
setITimer(struct itimerval* itime, int isec, int iusec,
        int sec, int usec) {
    itime->it_interval.tv_sec = isec;
    itime->it_interval.tv_usec = iusec;

    itime->it_value.tv_sec = sec;
    itime->it_value.tv_usec = usec;
}

void 
setITimerSec(struct itimerval* itime, int isec, int sec) {
    setITimer(itime, isec, 0, sec, 0);
}

int
main() {
    int i;
    struct itimerval itime;
    struct sigaction sa;
    sigset_t sigst;
    int sig;
    int alrmSignals[] = { SIGALRM, SIGVTALRM, SIGPROF};
    char *cp;
    struct timespec ts;
    siginfo_t si;

    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_sigaction = sigaction_handler;

    
    for(i=0; i<sizeof(alrmSignals)/sizeof(int); ++i) {
        if(sigaction(alrmSignals[i], &sa, NULL) < 0) {
            perror("sigaction ");
            return 1;
        }
    }

    printf("Initial time:%ld\n", time(NULL));
    setITimerSec(&itime, 3, 1);
    if(setitimer(ITIMER_REAL, &itime, NULL) < 0) {
        perror("setitimer");
        return EXIT_FAILURE;
    }

    setITimer(&itime,4, 0, 1, 1000*500 );
    if(setitimer(ITIMER_VIRTUAL, &itime, NULL) < 0) {
        perror("setitimer");
        return EXIT_FAILURE;
    }

    setITimer(&itime,2, 0, 3, 1000*500 );
    if(setitimer(ITIMER_PROF, &itime, NULL) < 0) {
        perror("setitimer");
        return EXIT_FAILURE;
    }

    sigemptyset(&sigst);
    sigaddset(&sigst, SIGQUIT);
    sigaddset(&sigst, SIGINT);
    if(sigprocmask(SIG_BLOCK, &sigst, NULL)) {
        perror("sigprocmask ");
        return 1;
    }
    /*!
     * sigwait sigtimedwait sigwaitinfo和
     * sigprocmask组合使用,sigwait会从
     * 阻塞的信号掩码队列中读取设置的信号集*/
    /*if(sigwait(&sigst, &sig) < 0) {
        perror("sigwait");
        return EXIT_FAILURE;
    }*/

    //为了测试SIGPROF和SIGVTALRM，做一个延时获取CPU时间
    ts.tv_sec = 1;
    ts.tv_nsec = 0;
    for(;;) {
        if(sigtimedwait(&sigst, &si, &ts) < 0) {
            if(errno != EINTR && errno != EAGAIN) {
                perror("sigtimedwait");
                return EXIT_FAILURE;
            }

            if(errno == EINTR) {
                printf("sigtimedwait inter\n");
                /*!被中断,执行代码获取CPU时间, 执行1.8s*/
                for(i=180; i; --i) elaspedTime();
            } else {
                printf("sigtimedwait超时...\n");
            }

        }  else {
            /*!获取到了信号*/
            sig = si.si_signo;
            break;
        }
    }

    psignal(sig, "received");

    return 0;
}




