/*!
 * Linux系统编程手册
 * P396
 * 习题22-1
 * 要求:给SIGCONT安装上信号处理函数并将其阻塞
 * sigaction(...)
 * sigprocmask(...)
 * 在此期间如果发送信号，则信号不会被信号处理器处理
 * 如果不对SIGCONT设置阻塞，则在收到SIGCONT信号后
 * 还是会先恢复进程的执行，然后再调用信号处理函数
 */

#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>

#include <sys/select.h>

static volatile sig_atomic_t gotSig = 0;
void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    psiginfo(si, "sigaction_handler");
    if(sig == SIGRTMIN) gotSig = 1;
}

int
main() {
    struct sigaction sa, oldSa;
    sigset_t st, oldst, st1;
    int i, n;
    struct timeval tv;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGCONT, &sa, &oldSa) < 0) {
        perror("sigaction ");
        return 1;
    }
    
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGRTMIN, &sa, &oldSa) < 0) {
        perror("sigaction ");
        return 1;
    }

    sigemptyset(&st);
    sigaddset(&st, SIGCONT);
    /*! 阻塞SIGCONT */
    if(sigprocmask(SIG_BLOCK, &st, NULL) < 0) {
        perror("sigprocmask ");
        return 1;
    }

    /*! 微妙microseconds */
    tv.tv_sec = 0;
    tv.tv_usec =  1000 * 200; //0.2s
    i=0;
    for(;;) {
        n = select(0, NULL, NULL, NULL, &tv);
        if(n < 0) {
            if(errno == EINTR) continue;
        } else if(n == 0) {
            if(gotSig) {
                /*!解除阻塞SIGCONT，解除SIGCONT之后才会调用action_handler */
                if(sigprocmask(SIG_UNBLOCK, &st, NULL) < 0) {
                    perror("sigprocmask ");
                    return 1;
                }
                break;
            }
            printf("tick [%d]...\n", i++);
        } 

        tv.tv_sec = 0;
        tv.tv_usec = 1000 * 200;
    }

    printf("Resume to run\n");

    return 0;
}

