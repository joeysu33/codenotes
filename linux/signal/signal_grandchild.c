/*!
 * 测试:
 * 进程A创建B, B创建C,如果C退出，
 * A和B谁会收到SIGCHLD信号，还是都收到，
 * 还是竞争关系
 * 答:如果C收到信号，C在监听，SIGCHLD只会传递给直接父亲B，
 * 如果B没有处理SIGCHLD则，按照SIGCHLD的默认行为处理，C的SIGCHLD
 * 不会传递给A，因为B是C的直接父亲
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    int status;
    /*!Unsafe in async signalIO*/
    printf("pid=[%d],ppid=[%d]:Received signal:%d, name:%s, from pid=%d\n",
            getpid(),
            getppid(),
            sig,
            strsignal(sig),
            si->si_pid);

    if(sig == SIGCHLD) {
        while(waitpid(-1, &status, WNOHANG) > 0) {
            printf("received: SIGCHLD, pid=%d\n", getpid());
        }
    }

    if(sig == SIGQUIT) {
        printf("I want to quit! [%d]\n", getpid());
        _exit(0);
    }
}

void
showPID(const char c) {
    printf("[%c]:pid=%d\n", c,getpid());
}

int main() {
    int i;
    pid_t pid;
    char name='A';
    struct sigaction sa, oldSa;
    struct sigaction *psa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;

    for(i=1; i<NSIG; ++i) {
        if(i == SIGCHLD) {
            psa = &oldSa;
        } else {
            psa = NULL;
        }
        sigaction(i, &sa, psa);
    }

    if(setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        perror("setvbuf");
        return 1;
    }

    showPID(name++);

    pid = fork();
    if(pid < 0) {
        printf("fork");
        return 1;
    } else if(pid == 0) {
        showPID(name++);
        //如果这里B取消对C的信号监听，信号是否会传递给A呢
        if(sigaction(SIGCHLD, &oldSa, NULL) < 0) {
            perror("sigaction");
            return 1;
        }
        pid = fork();
        if(pid < 0) {
            return 1;
        } else if(pid == 0) {
            showPID(name++);
            for(;;) pause();
            _exit(0);
        } else {
            for(;;) pause();
        }
        _exit(0);
    } else {
        for(;;) pause();
    }

    return 0;
}

