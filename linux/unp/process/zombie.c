/*!
 * SIGCHLD由子进程在自己退出的时候发出
 * 可以通过siginfo_t中的si_pid得到发送
 * 进程的PID信息
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <memory.h>
#include <string.h>

void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    /*! Unsafe in asyncIO */
    printf("signo:%d sig:%s frompid=%d\n", si->si_signo, strsignal(si->si_signo), si->si_pid);
    fflush(stdout);
}

int
main() {
    int i;
    int readed;
    pid_t pid;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGCHLD, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    printf("pid=%d\n", getpid());
    for(i=0; i<3; ++i) {
        switch( pid = fork()) {
            case -1: {
                         perror("fork");
                         return 1;
                     }
            case 0: {
                        printf("child-pid=%d\n", getpid());
                        _exit(0);
                    }
        }
    }

    pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    } else if(pid == 0) {
        /*!阻塞读取，在ps -e -o pid,ppid,state,nwchan中可以看到sleep进程信息*/
        readed = read(0, &i, sizeof(i));
        if(readed < 0) {
            perror("read");
            return 1;
        }
    }

    for(;;) pause();
    return 0;
}


