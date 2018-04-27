/*!
 * poll水平触发，一旦描述符非阻塞，则收到revents
 * ppoll与poll，增加了信号掩码
 * poll与select的区别在于poll不需要每次重置观察的fd,只需要设置进去即可
 * 因为有events和revents
 *
 * int poll(struct pollfd *fds, nfds_t nfds, int timeout);
 * struct pollfd {
 *    int fd; //文件描述符
 *    short events; //输入要观察的事件
 *    short revents; //返回观察的文件描述符上发生的事情
 * };
 * 如果events设置为0，什么都不观察，revents可能会收到POLLERR, POLLHUP, POLLINVAL;
 * POLLERR 错误条件
 * POLLHUP 挂起
 * POLLINVAL 描述符没有打开
 *
 * POLLIN  POLLRDNORM
 * POLLOUT POLLWRNORM
 *
 * 带外数据
 * POLLPRI  1.TCP紧急数据 2.在信包模式下伪终端状态变化，在slave模式
 * POLLRDBAND
 * POLLWRBAND
 *
 * POLLERR
 * POLLHUP
 * POLLINVAL
 *
 *
 *
 * A POLLHUP means the socket is no longer connected. In TCP, this means FIN has been received and sent.
 *
 * A POLLERR means the socket got an asynchronous error. In TCP, this typically means a RST has been received or sent. 
 * If the file descriptor is not a socket, POLLERR might mean the device does not support polling.
 *
 * For both of the conditions above, the socket file descriptor is still open, 
 * and has not yet been closed (but shutdown() may have already been called). 
 * A close() on the file descriptor will release resources that are still being reserved on behalf of the socket. 
 * In theory, it should be possible to reuse the socket immediately (e.g., with another connect() call).
 *
 * A POLLNVAL means the socket file descriptor is not open. It would be an error to close() it.
 *
 * 实现chatroom的server
 */

#include <sys/socket.h>
#include <poll.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIZE 10

int
main() {
    int sfd;
    struct pollfd fd[MAX_SIZE];
    return 0;
}


