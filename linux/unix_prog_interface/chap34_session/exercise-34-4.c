/*!
 * ???????
 * 验证当控制进程在收到SIGHUP信号，而不终止的时候，内核不会向
 * 前台进程组发送SIGHUP信号
 *
 * 1.需要确保当前进程是控制进程，（不知道怎么实现，可以新建一个session,但是需要一个控制终端来绑定)
 * 2.需要确保能接收SIGHUP信号的一定是前台进程
 *
 * 重点:控制进程设置SIGHUP的处理，测试进程作为前台进程
 *
 * 控制终端:是指会话首进程首次打开一个还没有成为某个会话的控制终端的终端时会建立控制终端
 * 控制进程:是指会话首进程打开了一个控制终端之后，它同时也成为了该控制终端的控制进程
 *
 * 简而言之，控制终端和控制进程是在首会话进程建立的时候建立起来的,一般而言会话进程所对应
 * 的进程就是控制进程
 */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void
sigaction_handler(int sig, siginfo_t *si, void* ucontext) {
    /*!Don't use this in async IO function */
    printf("pid=%d, signalno:%d, signalstr:%s.\n",
            getpid(),
            sig,
            strsignal(sig));
}

void
showProcInfo() {
    int st;
    pid_t pid;
    printf("PID=%d,PPID=%d PGRP=%d, SID=%d\n",
            getpid(),
            getppid(),
            getpgid(0),
            getsid(0));

    while((pid = waitpid(0, &st, WNOHANG)) > 0)  {
        printf("close pid=%d.\n", pid);
    }
}

int
main(int argc, char* argv[]) {
    pid_t pid;
    struct sigaction sa;

    showProcInfo();
    if(fork() > 0) {
        exit(0);
    }

    if(setsid() < 0) {
        perror("setsid");
        return 1;
    }

    setbuf(stdout, NULL);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGHUP, &sa, NULL) < 0) {
        perror("sigaction()");
        return 1;
    }

    pid = fork();
    showProcInfo();
    if(pid < 0) {
        perror("fork()");
        return 1;
    } else if (pid == 0) {
        printf("child created!\n");
    }

    /*!确保在60秒之后一定退出,ALARM信号如果不处理，默认退出*/
    alarm(60);

    for(;;) pause();
    return 0;
}

