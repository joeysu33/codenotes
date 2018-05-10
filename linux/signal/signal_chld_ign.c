/*!
 * 测试：
 * 将SIGCHLD设置为SIG_IGN可避免僵尸进程的产生
 * （虽然SIGCHLD默认的行为就是SIG_IGN)，
 * 来自Linux系统编程手册
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    pid_t pid;

    if(setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        perror("setvbuf");
        return 1;
    }

    //设置这一句和不设置区别很大
    //最好是采用waitpid的方式，这种方式虽然避免僵尸进程
    //但是没有管理好子进程的生命周期
    signal(SIGCHLD, SIG_IGN);
    for(i=0; i<5; ++i) {
        pid = fork();
        if(pid < 0) {
            perror("fork");
        } else if(pid == 0) {
            printf("child-pid=%d\n", getpid());
            _exit(0);
        } else {
            //Do nothin
        }
    }

    for(;;) pause();
    return 0;
}
