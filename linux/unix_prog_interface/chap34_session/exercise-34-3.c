/*!
 * 验证在进程组首进程中调用setsid()会失败
 * int setsid();
 *
 * setsid()调用会失败，当调用者是进程组的首进程的时候
 */

#include <unistd.h>
#include <stdio.h> //setsid

void
showPID() {
    printf("PID=%d, PPID=%d, PGID=%d, SID=%d.\n",
            getpid(),
            getppid(),
            getpgid(0),
            getsid(0));
}

int
main() {
    pid_t pid;

    showPID();
    pid = setsid();
    if(pid < 0) {
        perror("setsid");
        return 1;
    } 


    showPID();
    return 0;
}

