#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

void
sigaction_handler(int sig, siginfo_t *si, void* ucontext) {
    /*!Don't use this in async IO function */
    printf("signalno:%d, signalstr:%s.\n",
            sig,
            strsignal(sig));
}

void
showProcInfo() {
    printf("PID=%d,PPID=%d PGRP=%d, SID=%d\n",
            getpid(),
            getppid(),
            getpgid(0),
            getsid(0));
}

int
main(int argc, char* argv[]) {
    int i,j;
    pid_t pid;
    struct sigaction sa;

    setbuf(stdout, NULL);
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sigaction_handler;
    for(i=1; i<NSIG; ++i)
        sigaction(i, &sa, NULL);

    pid = fork();
    if(pid < 0) {
        perror("fork()");
        return 1;
    } else if (pid > 0) {
        showProcInfo();
        return 0; /* close parent*/
    }

    if(setsid() < 0) {
        perror("setsid");
        return 1;
    }
    showProcInfo();

    if(open("/dev/tty", O_RDWR) < 0) {
        perror("open-tty");
        return 1;
    }

    return 0;
}

