/*!
 * timer_XXX相比较alarm, setitimer等可以创建多个定时器，而
 * setitimer只能创建四种（每种只有一个),一共四个定时器
 * 使用信号的方式来接受timer定时器通知
 * int timer_create(clockid_t id, struct sigevent* ev, timer_t* timerid); //成功返回0，失败返回-1
 * int timer_settime(timer_t timerid, int flags, const struct itimerspec* value, struct itimerspec* oldvalue);
 * int timer_gettime(timer_t timerid, struct itimerspec* value);
 * int timer_delete(timer_t timerid);
 *
 * struct sigevent{
 *  int sigev_notify; //通知方式 SIGEV_SIGNAL(通过信号来通知) , SIGEV_NONE (不通知), SIGEV_THREAD(通过线程来通知), SIGEV_THREAD_ID(通过线程ID来进行通知
 *  int sigev_signo;  //信号数值
 *  union sigval sigev_value; //信号的数据 sigqueue,队列信号（实时信号）数据
 *
 *  union {
 *      pid_t _tid; //SIGEV_THREAD_ID模式下的线程ID
 *      struct {
 *          void(*_function) (union sigval); //SIGEV_THREAD模式下的线程函数
 *          void *_attribute;  //线程属性
 *      } _sigev_thread;
 *  }_sigev_un;
 * };
 *
 * sigev_notify_function 用宏代表_function
 * sigev_notify_attributes 用宏代表attribute
 */

#include <unistd.h> //pause()
#include <stdio.h>
#include <signal.h>
#include <time.h>  //timer_create, timer_settime, timer_delete...
#include <string.h>
#include <stdlib.h>
#include <memory.h>

#include <sys/time.h>

/*!
 * 如果siginfo_t* 没有获取到正确的值,code,value等
 * 基本就能确定sigaction的flags没有设置SA_SIGINFO
 */
void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    /*! Unsafe in async IO */
    printf("signo:%d, %s, code=%d, code-name:%s, value=%d\n", sig, strsignal(sig), si->si_code, (si->si_code==SI_TIMER) ? "SI_TIMER": "Other",si->si_value.sival_int);
    /*!定时器溢出 */
    printf("overrun=%d\n", si->si_overrun);
}


int 
main() {
    struct sigevent sev;
    struct sigaction sa;
    struct itimerspec its1, its2;
    timer_t timer,timer2;
    int i,j;

    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo  = SIGRTMIN;
    sev.sigev_value.sival_int = 100; //si->si_value->sival_int

    if(sigaction(SIGRTMIN, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }
    if(sigaction(SIGRTMIN+1, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    /*!
     * 创建CLOCK_REALTIME类型的定时器,定时器的ID: timer*/
    if(timer_create(CLOCK_REALTIME, &sev, &timer) < 0) {
        perror("timer_create ");
        return 1;
    }

    sev.sigev_notify = SIGEV_SIGNAL;
    sev.sigev_signo = SIGRTMIN+1;
    sev.sigev_value.sival_int = 200;
    if(timer_create(CLOCK_REALTIME, &sev, &timer2) < 0) {
        perror("timer_create ");
        return 1;
    }

    /*!
     * C语言的结构体默认是不初始化的
     * 不像C++, RAII*/
    its1.it_interval.tv_sec = 1;
    its1.it_interval.tv_nsec = 1000*1000*500;
    its1.it_value.tv_sec = 0;
    its1.it_value.tv_nsec = 1000*20;

    if(timer_settime(timer, 0, &its1, NULL) < 0) {
        perror("timer_settime ");
        return 1;
    }


    its1.it_interval.tv_sec = 2;
    its1.it_interval.tv_nsec = 1000*1000*100;
    its1.it_value.tv_sec = 5;
    its1.it_value.tv_nsec = 1000*10;

    if(timer_settime(timer2, 0, &its1, NULL) < 0) {
        perror("timer_settime ");
        return 1;
    }


    for(;;) pause();
    return 0;
}


