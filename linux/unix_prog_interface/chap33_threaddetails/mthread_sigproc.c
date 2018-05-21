/*!
 * 多线程的信号处理，
 * 1.在主线程中屏蔽所有的信号，新创建线程会从当前线程中继承屏蔽属性
 *   或者可以通过pthread_sigmask来设置
 * 2.单独创建一个线程来处理信号，使用sigwait, sigwaitinfo,sigtimedwait
 *   来处理屏蔽信号
 *
 * SIGPIPE只针对发生管道断裂的线程，其他的信号均针对进程，进程中的任何
 * 一个线程都有可能会处理信号，但是信号仅被处理一次。
 * 线程间发送信号
 *
 * int pthread_kill(pthread_t thread, int sig); //对指定的线程发送信号
 * int pthread_sigqueue(pthread_t thread, int sig, const union sigval value); //对指定的线程发送实时信号
 * 使用pthread_kill或pthread_sigqueue，如果目标线程并没有处理该信号，则该信号转由进程处理
 * pthread_kill(0)可以判断线程是否存活，和kill -0是一样的，判断进程是否存活
 * 使用signal或sigaction对信号的disposition是进程层面的
 *
 * 刚刚创建的新线程会从其创建者外继承信号掩码的一份拷贝
 */

#define _GNU_SOURCE

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#define handle_error(s, what) \
    do { errno = s; perror(what); exit(EXIT_FAILURE); }while(0)

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static __thread char tname[32];

void
showSigset(sigset_t *s) {
    int i;
    if(!s) return ;
    pthread_mutex_lock(&mtx);
    printf("%s has sigmask:", tname);
    for(i=1; i<NSIG; ++i) {
        if(sigismember(s, i)) {
            printf("\t%d:%s\n", i, strsignal(i));
        }
    }
    printf("\n");
    pthread_mutex_unlock(&mtx);
}

void*
threadFunc(void *arg) {
    int s, i;
    sigset_t st, oldst;

    /*!获取原来的线程信号掩码*/
    snprintf(tname, sizeof(tname)-1, "thread-%ld", (long)arg);
    sigemptyset(&st);
    s = pthread_sigmask(SIG_BLOCK, &st, &oldst);
    if(s) {
        handle_error(s, "pthread_sigmask");
    }
    showSigset(&oldst);

    /*! sleep for */
    for(;;) sleep(1);

    return NULL;
}

void*
sigProcThread(void* arg) {
    int r, i,s;
    sigset_t st, oldst;
    siginfo_t info;
    snprintf(tname, sizeof(tname)-1, "thread-%ld", (long)arg);

    /*!获取原来的信号掩码*/
    sigemptyset(&st);
    s = pthread_sigmask(SIG_BLOCK, &st, &oldst);
    if(s) {
        handle_error(s, "pthread_sigmask");
    }
    showSigset(&oldst);

    sigemptyset(&st);
    for(i=1; i<NSIG; ++i)
        sigaddset(&st, i);

    for(;;) {
        /*!处理信号,一次处理一个*/
        r = sigwaitinfo(&st, &info);
        if(r < 0) {
            handle_error(errno, "sigwaitinfo");
        }

        /*!对与线程中得到的信号进行单独分析*/
        printf("Received signal, signo:%d, strsignal:%s.\n", info.si_signo,
                strsignal(info.si_signo));
    }

    return NULL;
}

int 
main() {
    int i, s;
    long j;
    sigset_t st, oldst;
    pthread_t tid[3], tsig;
    void *retval;

    sigemptyset(&st);
    for(i=1; i<NSIG; ++i) 
        sigaddset(&st, i);
    s = pthread_sigmask(SIG_SETMASK, &st, &oldst);
    if(s) handle_error(s, "pthread_sigmask");
    showSigset(&st);

    for(i=0; i<sizeof(tid)/sizeof(pthread_t); ++i) {
        j = i+1;
        s = pthread_create(&tid[i], NULL, threadFunc, (void*)j);
        if(s) handle_error(s, "pthread_create");
    }
    s = pthread_create(&tsig, NULL, sigProcThread, (void*)100l);
    if(s) handle_error(s, "pthread_create");


    for(i=0; i<sizeof(tid)/sizeof(pthread_t); ++i) {
        pthread_join(tid[i], &retval);
        printf("thread-%d finished.\n", i+1);
    }
    pthread_join(tsig, NULL);

    /*! wait for signals*/
    for(;;) pause();

    return 0;
}

