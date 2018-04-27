/*!
 * nonblock client
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <memory.h>
#include <fcntl.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "nonblock_msg.h"

void
sendChatMsg(int fd, size_t* soff, nb_chatmsg_t* msg, char *closed) {
    int written;
    *closed = 0;

    /*!
     * 在非阻塞IO模式下,尽可能的多发送数据
     */
    for(;; ) {
        written = send(fd, (char*)msg + (*soff), nbChatMsgLen- (*soff), 0);
        if(written < 0) {
            if(errno == EAGAIN) {
                //没有更多的数据能发了
                printf("无法发送更多的数据...\n");
                break;
            }

            perror("written ");
            exit(2);
        } else if(written == 0) {
            /*!
             * 对方socket 已经关闭*/
            close(fd);
            *closed = 1;
        } else {
            (*soff) += written;
            (*soff) %= nbChatMsgLen;
            /*!
             * 一个完整数据发送完成，并退出
             */
            if((*soff) == 0) {
                *soff = 0; break;
            } else {
                printf("----发送数据:%d (bytes)\n", written);
            }
        }
    }
}

int
main(int argc, char*argv[]) {
    struct sockaddr_in addr;
    int fd, maxfd;
    const int infd = STDIN_FILENO;
    fd_set rfds;
    struct timeval tv;
    int n, readed, i, j;
    char linebuf[512];
    char *cp, *cp1;
    char name[20], to[20] = {0};
    nb_chatmsg_t smsg,rmsg;
    size_t soff, roff;
    char stclose;

    if(argc != 2) {
        perror("输入客户端名称\n");
        return 1;
    }

    name[sizeof(name)-1]=0;
    strncpy(name, argv[1], sizeof(name)-1);

    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd < 0) {
        perror("socket ");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(MSG_PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(fd, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect ");
        return 1;
    }

    /*!
     * socket非阻塞
     */
    if(fcntl(fd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }

    /*!
     * 标准输入非阻塞
     */
    if(fcntl(infd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }

    /*!发送一个姓名认证包*/
    stclose = 0;
    strcpy(smsg.m_from, name);
    strcpy(smsg.m_to, "server");
    strcpy(smsg.m_msg, "handshark");
    sendChatMsg(fd, &soff, &smsg, &stclose);

    if(stclose == 1) {
        close(fd);
        printf("服务器端关闭...\n");
        exit(1);
    }

    roff = 0;
    soff = 0;

    tv.tv_sec = 3;
    maxfd = (fd > infd) ? fd : infd;
    maxfd++;
    FD_ZERO(&rfds);
    FD_SET(infd, &rfds);
    FD_SET(fd, &rfds);
    maxfd++;

    for(;;) {
        n = select(maxfd, &rfds, NULL, NULL, NULL);
        if(n < 0) {
            perror("select ");
            exit(1);
        } else if(n==0) {
            printf("超时...\n");
        } else {
            /*!
             * 标准输入
             */
            if(FD_ISSET(infd, &rfds)) {
                readed = read(infd, linebuf, sizeof(linebuf)-1);
                if(readed < 0) {
                    if(errno == EAGAIN) {
                        printf("no more read....\n");
                    } else {
                        perror("read ");
                        exit(2);
                    }
                } else if(readed == 0) {
                    perror("infd-readed == 0 ");
                    exit(3);
                } else {
                    linebuf[readed]=0;
                    printf("line:%s\n", linebuf);
                    cp = strstr(linebuf, "@");
                    if(cp) {
                        for(cp++,cp1=cp; cp;cp++) {
                            if(*cp == ' ' || *cp == '\n') {
                                break;
                            }
                        }
                        i = cp-cp1;
                        if(i > 0) {
                            memcpy(to, cp1, i);
                            to[i]=0;
                        } else {
                            strcpy(to, "all");
                        }
                    } else {
                        strcpy(to, "all");
                    }

                    printf("准备将数据发送给:%s, 来自:%s\n", to, name);
                    strcpy(smsg.m_from, name);
                    strcpy(smsg.m_to, to);
                    memcpy(smsg.m_msg, linebuf, sizeof(linebuf));
                    stclose = 0;
                    sendChatMsg(fd, &soff, &smsg, &stclose);
                    if(stclose == 1) {
                        close(fd);
                        printf("服务器端关闭...\n");
                        exit(1);
                    }
                }
             }

            /*
             * fd
             */
            if(FD_ISSET(fd, &rfds)) {
                for(;;) {
                    readed = recv(fd, (char*)&rmsg + roff, nbChatMsgLen-roff, 0);
                    if(readed < 0) {
                        if(errno == EAGAIN) {
                            printf("fd无更多数据可读...\n");
                            break;
                        }
                        perror("recv ");
                        return 3;
                    } else if(readed == 0) {
                        printf("fd服务端关闭....\n");
                        exit(0);
                    } else {
                        roff += readed;
                        roff %= nbChatMsgLen;
                        if(roff == 0) {
                            printf("接收了一条完整的消息,来自:%s, 发给:%s,内容:%s\n", rmsg.m_from, rmsg.m_to, rmsg.m_msg);
                            break;
                        } else {
                            printf("----接受部分数据:%d (bytes)\n", readed);
                        }
                     }
                }
            }
        }

        FD_ZERO(&rfds);
        FD_SET(infd, &rfds);
        FD_SET(fd, &rfds);
        tv.tv_sec = 3;
    }

    return 0;
}
