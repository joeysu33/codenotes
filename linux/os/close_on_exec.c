/*!
 * 描述符上FD_CLOEXEC
 * 需要使用fcntl来设置标志位
 * int flag = fcntl(fd, F_GETFD);
 * flag |= FD_CLOEXEC;
 * fcntl(fd, F_SETFD, flag);
 *
 * 不能调用fcntl的F_SETFL来进行修改
 * 能在文件描述符打开之后进行修改的只有
 * O_APPEND
 * O_ASYNC
 * O_DIRECT
 * O_NOATIME
 * O_NONBLOCK
 *
 * 可以通过lsof来查看该文件的占用情况
 * fork copyonwrite
 */

#include <signal.h>
#include <unistd.h> //open execl
#include <fcntl.h>
#include <stdio.h>
#include <assert.h>

#include <sys/types.h> //mode_t
#include <sys/stat.h> //umask
#include <sys/wait.h> //waitpid

int
main(int argc, char* argv[]) {
    pid_t pid;
    int fd, fdflags, st, counter;
    mode_t lastmode;
    unsigned closeExec=0;
    
    if(argc > 1) closeExec=1;

    /*!
     * 消除掩码的影响，避免文件或文件夹在创建的过程
     * 中某些文件权限设置不上
     * */
    lastmode = umask(0);
    printf("lastmode=0%o\n", lastmode);
    fd = open("test.dat", O_RDWR | O_CREAT, 0666);
    if(fd < 0) {
        return 1;
    }

    if(closeExec) {
        fdflags = fcntl(fd, F_GETFD);
        if(fcntl(fd, F_SETFD, fdflags) < 0) {
            perror("fcntl ");
            return 1;
        }
        fdflags |= FD_CLOEXEC;
        if(fcntl(fd, F_SETFD, fdflags) < 0) {
            perror("fcntl ");
            return 1;
        }
    }

    pid = fork();
    if(pid < 0) {
        close(fd);
        perror("fork ");
        return 1;
    }
    else if(pid == 0) {
        /*!子进程会继承umask*/
        assert(umask(0) == 0);
        umask(lastmode);

        /*!如果设置了FD_CLOEXEC，那么在执行exec的时候就会
         * 自动关闭fd, execl的最后一个参数都是NULL */
        //if(execl("/bin/cat","-n","Makefile", NULL) < 0) {
        if(execl("/bin/sleep","30",NULL) < 0) {
            perror("execl ");
            return 1;
        }

        /*
        counter = 30;
        for(;counter ; counter--) {
            sleep(1);
            printf("counter = %d\n", counter);
        }
        */
        return 0;
    } else {
        close(fd);
        umask(lastmode);
        if(waitpid(pid, &st, 0) < 0) {
            perror("waitpid ");
            return 1;
        } 
        printf("status:%d\n", st);
    }

    return 0;
}



