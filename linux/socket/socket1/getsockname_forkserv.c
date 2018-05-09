/*!
 * 本程序用来测试，采用fork并发处理连接的情况
 * 如果父进程因为特殊情况关闭，子进程是否还可以继续通信
 * 答： 可以，因为进程的描述符表是独立的，操作系统内核对
 * 描述符有引用计数，不会关闭引用计数不为0的文件描述符
 *
 *
 * ------这里特别要注意的是------------
 *  输入不能是控制台，因为父进程退出之后，子进程会作为孤儿进程发给init进程,
 *  在ubuntu中实际上是startup进程，这个时候再对标准输入输出进行读写的话，
 *  会触发SIGTTOU信号，也就是不在终端的子进程中，却要对终端进行读写
 *  会导致进程被挂起
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

static FILE* sfp;

void
showSockAddr(const char* prefix,struct sockaddr_in* addr, int fd) {
    char buf[32];
    inet_ntop(AF_INET, &addr->sin_addr, buf, sizeof(buf));
    if(prefix) {
        fprintf(sfp,"%s:fd=%d, address=%s, port=%d\n", prefix, fd, buf, ntohs(addr->sin_port));
    } else {
        fprintf(sfp,"fd=%d, address=%s, port=%d\n", fd, buf, ntohs(addr->sin_port));
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
        fprintf(sfp,"==========%s=========\n", desc);
    }
    showSockName(fd);
    showPeerName(fd);
    fprintf(sfp,"\n");
}

int main() {
    time_t t;
    int sfd ;//fd[MAXCLIENT];
    int i, j,k, n, readed, written;
    struct sockaddr_in seraddr, cliaddr;
    socklen_t clilen;
    struct pollfd pfd[POLLMAX];
    char buf[32];
    char *at;
    pid_t pid;
    FILE *fp;

    fp = fopen("/home/ds/forkserv.log", "wa+");
    if(fp == NULL) {
        perror("fopen");
        return 1;
    }
    sfp = fp;

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
    fprintf(fp,"pid=%d, ppid=%d\n", getpid(), getppid());
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

                    pid = fork();
                    if(pid < 0) {
                        perror("fork");
                        return 1;
                    } else if(pid == 0) {
                        /*! Unsafe,回写数据, 为了简化过程，默认一次写入完成*/
                        /*!每隔一秒就发送一次数据，如果父进程已经关闭，子进程仍然可以访问，
                         * 每个进程有独立的文件描述符表,独立的子进程来与客户端通信*/
                        fprintf(fp,"cpid=%d, fd=%d\n", getpid(), j);
                        close(sfd);
                        for(k=0; k<POLLMAX; ++k) {
                            if(pfd[k].fd < 0) continue;
                            if(pfd[k].fd != j) {
                                /*!关闭不关心的文件描述符*/
                                close(pfd[i].fd);
                            }
                        }

                        for(k=200; k;--k) {
                            t = time(NULL);
                            at = ctime(&t);
                            written = write(j, at, strlen(at));
                            assert(written == strlen(at));
                            sleep(1);
                            fprintf(fp,"pid=%d\n, ppid=%d\n", getpid(), getppid());
                        }

                        _exit(0);
                    } else {
                        /*!父进程直接退出， 父进程中所有文件描述符均关闭*/
                        /*!父进程退出，子进程成为孤儿进程*/
                        j=0;
                        for(k=0; k<POLLMAX; ++k) {
                            if(pfd[k].fd > 0) {
                                j++;
                            }
                        }

                        /*!pfd[i]中的数据全部填满，则退出*/
                        if(j >= 6) {
                            fprintf(fp,"pid=%d, exit-----\n", getpid());
                            exit(0);
                        }
                    }
                } else {
                    /*!收发数据*/
                }
             }
        }
    }

    return 0;
}


