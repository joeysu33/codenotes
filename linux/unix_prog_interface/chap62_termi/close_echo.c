/*!
 * Close echo function of terminal
 *
 * int tcgetattr(int fd, struct termios *termios_p);
 * int tcsetattr(int fd, int option_actions, const struct termios *termios_p);
 *
 * 返回-1错误,fd必须是终端的文件描述符
 */

#include <stdio.h>
#include <termios.h> //tcgetattr, tcsetattr, ECHO
#include <unistd.h>

int
main() {
    struct termios tp;
    if(tcgetattr(STDIN_FILENO, &tp) < 0) {
        perror("tcgetattr");
        return 1;
    }

    tp.c_lflag &= ~ECHO;
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) < 0) {
        perror("tcsetattr");
        return 1;
    }

    printf("Close terminal echo-function.!\n");
    return 0;
}

