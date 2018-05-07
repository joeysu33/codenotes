/*!
 * 一道面试题
 * 在for循环中fork了3次，问一共产生了多少个子进程 答:7个，算上父进程的话8个
 * 需要考虑子进程自己也产生子进程
 * 对于这种题型，始终就是采用进程树的绘制方法来进行解答
 *
 * 父进程
 *   |
 *   |_1.第一个子进程
 *   |      |_2.第一个子进程的子进程
 *   |      |     |
 *   |      |     |---3.第一个子进程的子进程的子进程
 *   |      |     
 *   |      |_3.第一个子进程的第二个子进程
 *   |      
 *   |
 *   |_2.第二个子进程
 *   |      |_3.第二个子进程的子进程
 *   |
 *   |
 *   |
 *   |
 *   |_3.第三个子进程
 */
#include <unistd.h>
#include <stdio.h>

int 
main() {
    int i, n;
    pid_t pid;
    n = 3;

    /*!stdio标准输出没有缓冲，直接输出*/
    if(setvbuf(stdout, NULL, _IONBF, 0)) {
        perror("setvbuf");
        return 1;
    }

    printf("parent-pid=%d\n", getpid());

    for(i=0; i<3; ++i) {
        pid = fork();
        if(pid < 0) {
            perror("fork");
            return 1;
        } else if(pid == 0) {
            printf("pid=%d\n", getpid());
        } else {
            printf("-----[pid]=%d\n", getpid());
        }
    }

    return 0;
}
