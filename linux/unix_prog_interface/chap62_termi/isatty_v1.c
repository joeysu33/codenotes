/*!
 * 通过tcgetattr来实现isatty函数
 * int tcgetattr(int fd, const struct termios* tp);
 * 如果fd不是终端相关的描述符tcgetattr返回-1，错误信息是ENOTTY
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>

int
main() {
    int isatty = 1;
    struct termios ter;
    if(tcgetattr(STDIN_FILENO, &ter) < 0) {
        if(errno == ENOTTY) { isatty = 0;}
    }     
    printf("STDIN_FILENO is:%s.\n", isatty ? "atty" : "not atty");
    return 0;
}
