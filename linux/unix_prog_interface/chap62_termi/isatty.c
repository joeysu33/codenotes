/*!
 * 判断描述符是否关联一个终端设备
 */

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <fcntl.h>

#define ISTTY(fd) \
    do { showIsTTY(fd, #fd); } while(0)

void
showIsTTY(int fd, const char *desc) {
    char *name;
    int istty= isatty(fd);
    if(istty) {
        name = ttyname(fd);
    } else {
        name = "nil";
    }

    printf("%s:%d %s, ttyname=%s\n", desc, fd, istty ? "is tty!" : "is not tty!", name);
}

int 
main() {
    int fd;
    ISTTY(STDIN_FILENO);
    ISTTY(STDOUT_FILENO);
    ISTTY(STDERR_FILENO);

    fd = open("test.txt", O_WRONLY | O_CREAT, 0666);
    if(fd < 0) {
        perror("open");
        return 1;
    }

    showIsTTY(fd, "test.txt");
    close(fd);

    return 0;
}

