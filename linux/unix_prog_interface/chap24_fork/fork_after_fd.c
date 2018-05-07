/*!
 * 为了检验fork之后的fd，
 * 1.是否发生了拷贝 答:发生了拷贝
 * 2.fd的值是否相同（应该不同但是都指向同一内核文件，采用类似dup来拷贝)     答:fd的值是一样的，都是内存页拷贝，但是指向同一个内核文件对象
 */

#include <memory.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h> //O_CREAT , O_APPEND , O_WRONLY
#include <string.h> //strlen
#include <stdlib.h>

#include <sys/wait.h> //wait, waitpid, waittid

void showfd(int fd) {
    /*!这里要注意，多个进程调用该函数,pid现取*/
    char buf[PATH_MAX];
    char pathname[PATH_MAX];

    /*!注意getpid() */
    snprintf(pathname, sizeof(pathname), "/proc/%d/fd/%d", getpid(), fd);
    if(readlink(pathname, buf, sizeof(buf)) < 0) {
        perror("readlink");
    } else {
        printf("pid=%d, fd=%d, fd-file:%s\n",getpid(), fd, buf);
    }
}

int main() {
    int fd;
    pid_t pid;
    char rbuf[16];

    memset(rbuf, 0, sizeof(rbuf));
    /*!文件不存在则创建，增加O_APPEND，保证原子增加写*/
    fd = open("test.dat", O_CREAT | O_WRONLY | O_APPEND, 0666);
    if(fd < 0) {
        perror("open");
        return 1;
    }

    printf("init-fd=%d, parent-pid=%d\n", fd, getpid());
    pid = fork() ;
    switch(pid) {
        case -1: {
                     perror("fork");
                     return 1;
                 }
        case 0: {
                    printf("child go!\n");
                    showfd(fd);
                    snprintf(rbuf, sizeof(rbuf)-1, "%d:hello!!", getpid());
                    if(write(fd, rbuf, strlen(rbuf)) < 0) {
                        perror("write");
                    }
                    close(fd);
                    break;
                }
                /*! > 0*/
        default: {
                    printf("parent go!\n");
                    showfd(fd);
                    snprintf(rbuf, sizeof(rbuf)-1, "%d:hello", getpid());
                    if(write(fd, rbuf, strlen(rbuf)) < 0) {
                        perror("write");
                    }
                    close(fd);
                    waitpid(pid, NULL, 0);
                    break;
                }
    }

    return 0;
}

