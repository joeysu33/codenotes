/*!
 * 进程组和会话
 * 会话由多个进程组组成
 * 进程组由多个进程组成
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int 
main() {
    printf("pid=%d, ppid=%d, pgid=%d, sid=%d\n",
            getpid(),
            getppid(),
            getpgid(0),
            getsid(0));
    return 0;
}
