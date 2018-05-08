/*!
 * 通过测试可知，listenfd只能获取getsockname，因为没有建立连接信道，所以得不到对端信息
 * 所有accept的可以得到本地地址和对端地址
 */
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <assert.h>

#include <sys/socket.h>
#include <sys/poll.h>

#include <netinet/in.h> //sockaddr
#include <arpa/inet.h> //inet_addr, inet_pton, inet_ntop, inet_aton, inet_ntoa

#define MAXCLIENT 10
#define SERVPORT 6666
#define BACKLOG 16
#define POLLMAX 10

void
showSockAddr(const char* prefix,struct sockaddr_in* addr, int fd) {
    char buf[32];
    inet_ntop(AF_INET, &addr->sin_addr, buf, sizeof(buf));
    if(prefix) {
        printf("%s:fd=%d, address=%s, port=%d\n", prefix, fd, buf, ntohs(addr->sin_port));
    } else {
        printf("fd=%d, address=%s, port=%d\n", fd, buf, ntohs(addr->sin_port));
    }

}

void
showSockName(int fd) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(getsockname(fd, (struct sockaddr*)&addr, &len) < 0) {
        perror("getsockname");
        exit(1);
    }
    showSockAddr("sockname", &addr, fd);
}

void
showPeerName(int fd) {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(getpeername(fd, (struct sockaddr*)&addr, &len) < 0) {
        perror("getpeername");
        /*! 这里因为listenfd是得不到的，所以暂不退出*/
        return;
    }
    showSockAddr("peername", &addr, fd);
}

void
showSockAndPeerName(int fd, const char *desc) {
    if(desc) {
        printf("==========%s=========\n", desc);
    }
    showSockName(fd);
    showPeerName(fd);
    printf("\n");
}

int main() {
    time_t t;
    int sfd, fd[MAXCLIENT];
    int i, j,k, n, readed, written;
    struct sockaddr_in seraddr, cliaddr;
    socklen_t clilen;
    struct pollfd pfd[POLLMAX];
    char buf[32];
    char *at;

    sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sfd < 0) {
        perror("socket");
        return 1;
    }

    if(fcntl(sfd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl");
        return 1;
    }

    memset(&seraddr, 0, sizeof(seraddr));
    seraddr.sin_port = htons(SERVPORT);
    seraddr.sin_family = AF_INET;
    if(inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr) != 1) {
        perror("inet_pton");
        return 1;
    }
    if(bind(sfd, (const struct sockaddr*)&seraddr, sizeof(seraddr)) < 0) {
        perror("bind");
        return 1;
    }
    if(listen(sfd, BACKLOG) < 0) {
        perror("listen");
        return 1;
    }

    memset(pfd, 0, sizeof(pfd));
    for(i=0; i<POLLMAX; ++i) {
        pfd[i].fd = -1;
    }

    pfd[0].fd = sfd;
    pfd[0].events = POLLIN;
    showSockAndPeerName(sfd, "listenfd");

    for(;;) {
        n = poll(pfd, POLLMAX, -1);
        if(n < 0) {
            if(errno == EINTR) continue;
            perror("poll");
            return 1;
        } else {
            for(i=0; i<POLLMAX; ++i) {
                if(pfd[i].fd < 0 || !(pfd[i].revents & POLLIN)) continue;
                if(pfd[i].fd == sfd) {
                    clilen = sizeof(cliaddr);
                    j = accept(sfd, (struct sockaddr*)&cliaddr, &clilen);
                    if(j < 0) {
                        perror("accept");
                        return 1;
                    }

                    /*!
                     * 将新的fd加入到pollfd*/
                    for(k=0; k<POLLMAX;++k) {
                        if(pfd[k].fd < 0) {
                            pfd[k].fd = j;
                            pfd[k].events = POLLIN;
                            memset(buf, 0, sizeof(buf));
                            snprintf(buf, sizeof(buf), "client[%d]", k);
                            showSockAndPeerName(j, buf);
                            break;
                        }
                    }

                    if(fcntl(j, F_SETFL, O_NONBLOCK) < 0) {
                        perror("fcntl");
                        return 1;
                    }

                    /*! Unsafe,回写数据, 为了简化过程，默认一次写入完成*/
                    t = time(NULL);
                    at = ctime(&t);
                    written = write(j, at, strlen(at));
                    assert(written == strlen(at));
                } else {
                    /*!收发数据*/
                }
             }
        }
    }

    return 0;
}


