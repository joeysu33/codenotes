/*!
 * linux上的system()函数
 * int system(const char *cmd);
 * 1.fork出一个进程
 * 2.执行exec,执行shell
 * 3.在shell下fork出一个子进程，或多个
 * 4.在shell中执行execve，执行子进程
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    system("ls -l | wc -l ");
    return 0;
}

