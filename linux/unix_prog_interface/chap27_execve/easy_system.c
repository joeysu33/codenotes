/*!
 * 通过bash -c "cmd"来实现简易版本的system
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*!
 * system都是阻塞运行*/
int
easy_system(const char* cmd) {
    pid_t pid;
    int status;
    char buf[1024];

    /*!这里加不加"都没事 */
    snprintf(buf, sizeof(buf), "\"%s\"", cmd);
    pid = fork();
    if(pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /*!包含可执行文件的第一个参数*/
        execl("/bin/bash" ,"bash", "-c", cmd, NULL);
        _exit(127); //execlp执行失败，返回127
    } else {
        if(waitpid(-1, &status, 0) < 0) {
            perror("waitpid");
            return 2;
        } else {
            /*!执行成功返回子进程状态 */
            return status;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    return easy_system("/bin/ls");
}


