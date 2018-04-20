/*!
 * 信号接收，接收所有传递过来的信号
 * 使用非实时信号进行测试
 * 首先设置进程的信号集处理，然后再sleep,在sleep期间发送大量的信号，
 * 检测最后接收着接收到了多少信号
 */

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> //strsignal

//NSIG 已经在<signal.h>中定义
//sigset_t int[32]
//NSIG 65 包含实时信号，从1开始

static volatile sig_atomic_t gotSignal = 0;
static volatile int sigCnt[NSIG];
/*! const volatile */
static const volatile int sc_const;

static void 
handler_signals(int sig) {
    if(sig == SIGINT) {
        gotSignal = 1;
    } else {
        sigCnt[sig]++;
    }
}

void 
dumpSignalSet(sigset_t *s, const char *prefix, FILE *stream) {
    int i;
    FILE *st ;

    if(!s) return ;
    st = (stream) ? stream : stdout;
    for(i=1; i<NSIG; ++i) {
        if(sigismember(s, i)) {
            fprintf(st, "%s sig=%d strsig=%s\n", prefix, i, strsignal(i));
        }
    }
}

void 
dumpSignalSet2(sigset_t *s, FILE* stream) {
    dumpSignalSet(s, "\t\t", stream);
}

void 
dumpSignalSet1(sigset_t *s ) {
    dumpSignalSet2(s, stdout);
}

int
main(int argc, char* argv[]) {
    int i;
    int waitSecs;
    sigset_t s, oldset, pendingMask;

    /*!给所有的信号，加上处理函数*/
    for(i=1; i<NSIG; ++i)
        signal(i, handler_signals);

    waitSecs = 10;
    if(argc > 1) {
        waitSecs = atoi(argv[1]);
        if(waitSecs < 1) waitSecs = 10;
    }

    /*!设置信号屏蔽掩码*/
    sigfillset(&s);
    if(sigprocmask(SIG_SETMASK, &s, &oldset) == -1) {
        perror("sigprocmask ");
        return 1;
    }

    printf("%s: Sleep for %d seconds.\n", argv[0], waitSecs);
    sleep(waitSecs);

    /*!获取当前阻塞的屏蔽掩码*/
    if(sigpending(&pendingMask) == -1) {
        perror("sigpending ");
        return 2;
    }

    printf("%s: Pending signals are:\n", argv[0]);
    dumpSignalSet1(&pendingMask);

    /*!恢复原来的屏蔽掩码*/
    sigemptyset(&s);
    if(sigprocmask(SIG_SETMASK, &s, &oldset) == -1) {
        perror("sigpromask ");
        return 3;
    }

    /*!等待SIGINT信号*/
    while(!gotSignal) ;

    /*!打印在设置掩码之后，屏蔽信号期间，捕捉到的信号数目*/
    for(i=1; i<NSIG; ++i) {
        if(sigCnt[i] > 0) {
            printf("sig-%d = %d\n", i, sigCnt[i]);
        }
    }

    exit(0);
}



