/*!
 * pid_t wait(int *status);
 * 返回终止进程的ID值，错误返回-1
 */

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main() {
    int status;
    pid_t pid;

    pid = fork();
    if(pid < 0) {
        perror("fork");
        return 1;
    } else if(pid == 0) {
        printf("pid=%d, start to sleep 3 sec!\n", getpid());
        sleep(3);
        _exit(100);
    } 

    pid = fork();
    if(pid < 0) {
        perror("fork");
        return 1;
    } else if(pid == 0) {
        printf("pid=%d, start to sleep 1 sec!\n", getpid());
        sleep(1);
        _exit(200);
    }

    //wait到100的子进程
    pid = wait(&status);
    printf("received pid=%d, status=%d\n", pid, status);

    //wait到200的子进程
    printf("rewait...\n");
    pid = wait(&status);
    printf("received pid=%d, status=%d\n", pid, status);

    //wait不到
    printf("rewait...\n");
    pid = wait(&status);
    printf("received pid=%d, status=%d\n", pid, status);
    if(pid < 0) {
        perror("wait");
    }

    return 0;
}

