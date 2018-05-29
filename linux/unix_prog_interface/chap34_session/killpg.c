/*!
 * kill进程组
 * int killpg(pid_t pgid, int sig);
 * 返回-1错误，当pgid为0，使用调用进程的pid
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <memory.h>

void
sighandler(int sig, siginfo_t* si, void* context) {
    /*!It's not safe in async for printf strsignal */
    printf("pid=%d signo:%d signal:%s.\n",
            getpid(),
            si->si_signo,
            strsignal(si->si_signo));
}

void
showPID() {
    printf("PID=%d, PPID=%d, PGID=%d, SID=%d.\n",
            getpid(),
            getppid(),
            getpgid(0),
            getsid(0));
}

int
main(int argc, char* argv[]) {
    int i, j;
    struct sigaction sa;
    pid_t pid;

    setbuf(stdout, NULL);
    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sa.sa_sigaction = sighandler;

    for(i=1; i<NSIG; ++i)  {
        sigaction(i, &sa, NULL);
    }

    showPID();
    for(i=0; i<3; ++i) {
        pid = fork();
        if(pid < 0) {
            perror("fork");
            return 1;
        } else if(pid == 0) {
            showPID();
            pause();
            _exit(0);
        }
    }

    sleep(3);
    killpg(0, SIGQUIT);
    return 0;
}

