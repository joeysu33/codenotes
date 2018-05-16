/*!
 * 问题：
 * 1.建立SIGCHLD的信号处置
 * 2.屏蔽该SIGCHLD信号
 * 3.fork一个子进程
 * 4.waitpid该子进程
 * 5.取消屏蔽
 *
 * 问：信号处置函数是否还会收到该信号
 * 答：能
 *
 * 说明了一个问题:如果使用waitpid就不要屏蔽SIGCHLD信号
 * 在SIGCHLD信号中调用waitpid，否则先屏蔽SIGCHLD，而后
 * 调用waitpid，该SIGCHLD信号仍然会接收到。
 *
 * 有一点是可以肯定的，如果使用waitpid，可以屏蔽，但是一定不能忽略SIGCHLD信号
 * 否则会导致waitpid一直等待下去，因为忽略SIGCHLD信号会导致收不到task_struct，
 * 连僵尸的尸体都木有了。
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/wait.h>

void
sigaction_handler(int sig, siginfo_t *si, void* ucontext) {
    /*! Unsafe in sig asyncIO, printf, strsignal */
    printf("Receive signo:%d, %s\n", sig, strsignal(sig));
}

int
main() {
    pid_t pid;
    struct sigaction sa;
    sigset_t st, oldst;
    int status;
    int i;

    //case1
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGCHLD, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    //case2
    sigemptyset(&st);
    sigaddset(&st, SIGCHLD);
    if(sigprocmask(SIG_BLOCK, &st, &oldst) < 0) {
        perror("sigprocmask");
        return 1;
    }

    printf("parent pid=%d.\n", getpid());
    //case3
    pid = fork();
    if(pid < 0) {
        perror("fork");
        return 1;
    } else if(pid == 0) {
        printf("child pid=%d.\n", getpid());
        sleep(1);
        _exit(0);
    } else {
        //case4
        for(;;) {
            i = waitpid(pid, &status, 0) ;
            if(i < 0 && i != EINTR) {
                perror("waitpid");
                return 1;
            } else {
                printf("waited:%d.\n", i);
                break;
            }
        }

        //case5
        if(sigprocmask(SIG_SETMASK, &oldst, NULL) < 0) {
            perror("sigprocmask");
            return 1;
        }
    }

    sleep(5);
    return 0;
}

