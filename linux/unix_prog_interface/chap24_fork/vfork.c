/*!
 * vfork和fork的区别
 * 1.使用vfork构建的子进程在_exit或exec或异常退出（信号)，之前共享父进程内存空间
 * 2.在子进程退出之前，父进程会自动阻塞
 * 3.调用vfork之后，一定会先执行子进程
 *
 * 特别需要注意的是，vfork或者fork的子进程退出要使用_exit
 * exit和_exit的区别是exit会自动刷新缓冲区，但是_exit不会
 * exit在内部调用_exit
 */

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

static int stk ;
int main() {
    int istk;
    pid_t pid;
    istk = 0;
redo:
    switch(pid = vfork()) {
        case -1: { 
                     if(errno == EINTR) goto redo;
                     exit(1);
                 }
        case 0: { 
                    printf("child go!\n");
                    istk = 1000;
                    stk = 2000;
                    usleep(1000* 1000 * 3);
                    //这里子进程要调用_exit，不会对父进程描述符缓存区造成影响
                    _exit(1);
                }
        default: { 
                     printf("parent go!\n");
                     printf("istk=%d, stk=%d\n", istk, stk);
                     break; 
                 }
    }

    return 0;
}

