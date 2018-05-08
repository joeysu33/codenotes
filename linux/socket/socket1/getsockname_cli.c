#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/poll.h>

#define MAXCLIENT 10
#define SERVPORT 6666
#define POLLMAX MAXCLIENT

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
        return ;
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


int
main() {
    struct pollfd pfd[POLLMAX];
    int fd[MAXCLIENT];
    int i, j,n, readed;
    struct sockaddr_in seraddr;
    char buf[10240];

    memset(&seraddr, 0, sizeof(seraddr));
    if(inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr) != 1) {
        perror("inet_pton");
        return 1;
    }
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(SERVPORT);

    for(i=0; i<MAXCLIENT; ++i) {
        fd[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(fd[i] < 0) {
            perror("socket");
            return 1;
        }

        if(connect(fd[i], (const struct sockaddr*)&seraddr, sizeof(seraddr)) < 0) {
            perror("connect");
            return 1;
        }

        pfd[i].fd = fd[i];
        pfd[i].events = POLLIN;

        if(fcntl(fd[i], F_SETFL, O_NONBLOCK) < 0) {
            perror("fcntl");
            return 1;
        }

        snprintf(buf, sizeof(buf), "fd[%d]", i);
        showSockAndPeerName(fd[i], buf);
    }

    for(;; ) {
        n = poll(pfd, POLLMAX, -1);
        if(n < 0) {
            if(errno == EINTR) continue;
            perror("poll");
            return 1;
        } else {
            /*!监听数据到来*/
            for(i=0; i<MAXCLIENT; ++i) {
                if(pfd[i].fd < 0 || !(pfd[i].revents & POLLIN)) continue;
                readed = read(pfd[i].fd, buf, sizeof(buf));
                if(readed < 0) {
                    perror("read");
                    return 1;
                } else if(readed == 0) {
                    close(pfd[i].fd);
                    pfd[i].fd = -1;
                    fd[i] = -1;
                } else {
                    /*!Unsafe，这里默认一次读完了，真实情况是否读取完全，需要设置数据结构，定义数据边界*/
                    assert(readed < sizeof(buf));
                    buf[readed] = 0;
                    printf("fd[%d]-readed:%s\n", fd[i], buf);
                }
            }
        }
    }

    return 0;
}
