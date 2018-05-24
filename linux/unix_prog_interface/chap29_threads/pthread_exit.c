/*!
 * 如果主线程调用pthread_exit()程序会退出吗，会，因为没有任何线程了
 * 如果还有别的线程仍然在执行的话，整个程序是不会退出的
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int 
main() {
    printf("PID=%d, PPID=%d, TID=0x%lx.\n", getpid(), getppid(),pthread_self());
    printf("Ready to call pthread_exit!\n");
    pthread_exit(0);
    printf("Finish to call pthread_exit!\n");
    return 0;
}

