/*!
 * 编写一个程序验证调用vfork之后
 * 子进程可以关闭一个文件描述符，而不影响父进程的文件描述符
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <sys/types.h> //mode_t
#include <sys/stat.h>  //umask

int main() {
    pid_t pid;
    int fd;
    const char* pathname = "test1.dat";
    mode_t oldmode;

    /*!将umask设置为0*/
    oldmode = umask(0);
    fd = open(pathname, O_CREAT | O_WRONLY | O_APPEND, 0666);
    if(fd < 0) {
        perror("open");
        return 1;
    }

    pid = vfork();
    if(pid < 0) {
        perror("vfork");
        return 1;
    } else if(pid == 0) {
        /*!vfork中虽然子进程共享父进程的内存，但是文件描述符是基于进程来分配的
         * 在vfork中文件描述符会被复制一份，所以如果在子进程中关闭描述符对父进程没有影响*/
        printf("child close(0);\n");
        sleep(2);
        close(STDOUT_FILENO);
        if(write(fd, "aabb", 4) != 4) {
            perror("write");
        }
        close(fd);
        _exit(0);
    } else {
        printf("parent-test\n");
        if(write(fd, "cckk", 4) != 4) {
            perror("write");
        }
        close(fd);
        /*! 恢复*/
        umask(oldmode);
    }

    return 0;
}

