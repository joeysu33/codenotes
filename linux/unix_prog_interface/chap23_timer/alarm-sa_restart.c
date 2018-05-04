/*!
 * 目的：检查如果SIGALRM和SA_RESTART一起使用的后果
 * SIGALRM信号不可以和SA_RESTART一起使用，
 * 1.使用SA_RESTART，read阻塞调用会一直等下去，因为
 * 　３秒之内没有输入的话，就会触发alarm，调用完成
 *   信号处理之后，会继续调用read函数
 * 2.不使用SA_RESTART, read阻塞的过程中如果收到了alarm
 *   信号，对返回-1, 错误码是:EINTR
 *
 * 如果希望将定时器作为超时的工具的话，不要给sigaction设置SA_RESTART标志位
 * 可以通过EINTR作为超时的标志
 * n = read(STDIN_FILENO, buf, sizeof(buf));
 * if( n < 0) {
 *    if(errno == EINTR) {
 *  　　//阻塞调用已经超时
 *    } else {
 *      //发生了错误
 *    }
 * } else {...}
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h> //alarm
#include <string.h> //strsignal

#include <sys/times.h> //times
#include <sys/time.h> //time

void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    /*! Unsafe call for async I/O */
    printf("signalno:%d, signalinfo:%s\n", sig, strsignal(sig));
}


int
main() {
    int n;
    char buf[16];
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; //针对SIGALRM信号，使用了SA_RESTART标识
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGALRM, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    alarm(3);
    n = read(STDIN_FILENO, buf, sizeof(buf));
    if(n < 0) {
        perror("read");
        return 1;
    }

    return 0;
}

