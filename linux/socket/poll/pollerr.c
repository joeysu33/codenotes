/*!
 * 对POLLERR 收到或发送RST（重连）位的TCP包
 * POLLHUP 对端socket关闭
 * POLLINVAL
 * 进行分析
 * 什么情况下会触发
 */

#define _XOPEN_SOURCE 700
#include <fcntl.h> /* creat, O_CREAT */
#include <poll.h> /* poll */
#include <stdio.h> /* printf, puts, snprintf */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */
#include <unistd.h> /* read */

int main(void) {
    char buf[1024];
    int fd, n;
    short revents;
    struct pollfd pfd;

    fd = open("poll0.tmp", O_RDONLY | O_NONBLOCK);
    pfd.fd = fd;
    pfd.events = POLLIN;
    while (1) {
        puts("loop");
        poll(&pfd, 1, -1);
        revents = pfd.revents;
        if (revents & POLLIN) {
            n = read(pfd.fd, buf, sizeof(buf));
            printf("POLLIN n=%d buf=%.*s\n", n, n, buf);
        }
        if (revents & POLLHUP) {
            printf("POLLHUP\n");
            close(pfd.fd);
            pfd.fd *= -1;
        }
        if (revents & POLLNVAL) {
            printf("POLLNVAL\n");
        }
        if (revents & POLLERR) {
            printf("POLLERR\n");
        }
    }
}
