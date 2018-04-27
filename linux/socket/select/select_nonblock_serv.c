/*!
 * 非阻塞的IO select
 * 服务端可以发送给所有人，其他的可以相互发送
 */
#define _GNU_SOURCE

#include <sys/select.h>
#include <sys/socket.h>

#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h> //inet_addr

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <fcntl.h>
#include <errno.h>

#include "nonblock_msg.h"

#define MAX_CLIENT 10

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
             * 一个完整数据发送完成,并退出
             */
            if((*soff) == 0) {
                *soff = 0; break;
            } else {
                printf("----发送数据:%d (bytes)\n", written);
            }
        }
    }
}

int hasClient(int *client, int n) {
    int cnt, i;
    if(!client) return 0;
    for(i=0,cnt=0; i<n; ++i) {
        if(client[i] < 0) continue;
        cnt++;
    }

    return cnt;
}

int
main() {
    const int infd = STDIN_FILENO;
    int sfd, client[MAX_CLIENT];
    int i,j, maxfd, n;
    int readed;
    fd_set rfds;
    struct timeval tv;
    struct sockaddr_in addr, caddr;
    char stclose;
    socklen_t cAddrLen;
    char linebuf[128];
    char firstmsg[MAX_CLIENT];

    /*!
     * 给每个客户端用来接收完整的数据
     */
    nb_chatmsg_t rmsgs[MAX_CLIENT];
    size_t rmsgoff[MAX_CLIENT];
    char client_name[MAX_CLIENT][20];

    /*!
     * 每个客户端的发送缓存
     */
    nb_chatmsg_t smsgs[MAX_CLIENT];
    size_t smsgoff[MAX_CLIENT];

    nb_chatmsg_t servmsg;


    sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sfd < 0) {
        perror("socket ");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(MSG_PORT);
    if(bind(sfd, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind ");
        return 1;
    }

    if(listen(sfd, 5) < 0) {
        perror("listen ");
        return 1;
    }

    /*!
     * 将server设置为非阻塞
     */
    if(fcntl(sfd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }
    /*!
     * 标准输入设置为非阻塞
     */
    if(fcntl(infd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }

    for(i=0; i<MAX_CLIENT; ++i) {
        client[i]=-1;
        memset(&rmsgs[i], 0, sizeof(nb_chatmsg_t));
        rmsgoff[i]=0;
        client_name[i][0]=0;
        firstmsg[i]=1;
    }

    maxfd = (sfd > infd) ? (sfd+1) : (infd +1);

    FD_ZERO(&rfds);
    FD_SET(sfd, &rfds);
    FD_SET(infd, &rfds);
    tv.tv_sec = 3;
    for(;;) {
        n = select(maxfd, &rfds, NULL, NULL, NULL);
        if(n < 0) {
            perror("select ");
            exit(1);
        } else if( n== 0) {
            printf("超时...\n");
        } else {
            /*!新连接
             */
            if(FD_ISSET(sfd, &rfds)) {
                cAddrLen = sizeof(caddr);
                for(j=0; j<MAX_CLIENT; ++j) {
                    if(client[j] < 0) break;
                }
                if(j == MAX_CLIENT) {
                    printf("客户端达到上限!\n");
                } else {
                    i=accept(sfd, (struct sockaddr*)&caddr, &cAddrLen);
                    if(i < 0) {
                        perror("accept ");
                        exit(1);
                    } else {
                        printf("新的连接:%d\n", i);
                        client[j] = i;
                        sprintf(client_name[j], "%02d", i);
                        rmsgoff[j]=0;
                        smsgoff[j]=0;
                        firstmsg[j]=1;
                    }
                }
            }

            /*!
             * 输入
             */
            if(FD_ISSET(infd, &rfds)) {
                /*!
                 * 尽可能的多读
                 */
                for(;;) {
                    readed = read(infd, linebuf, sizeof(linebuf)-1);
                    if(readed < 0) {
                        if(errno == EAGAIN) {
                            break;
                        }
                        perror("read ");
                        exit(3);
                    } else if(readed == 0) {
                        perror("readed == 0 ");
                        exit(3);
                    } else {
                        linebuf[readed]=0;
                        printf("line:%s\n", linebuf);
                        /*!
                         * 发送给所有的客户端
                         */
                        memcpy(servmsg.m_msg, linebuf, sizeof(linebuf));
                        strcpy(servmsg.m_from, "server");
                        for(j=0; j<MAX_CLIENT; ++j) {
                            if(client[j] < 0) continue;
                            /*!
                             * 上次未发送完成的数据
                             */
                            if(smsgoff[j] != 0) {
                                printf("******[line]发送未发送完成的数据给:%s,来自:%s\n", smsgs[j].m_from, smsgs[j].m_to);
                            } else {
                                /*!拷贝新数据进行发送*/
                                strcpy(servmsg.m_to, client_name[j]);
                                //sprintf(servmsg.m_to, "%d", client[j]);
                                memcpy(&smsgs[j], &servmsg, nbChatMsgLen);
                            }

                            stclose = 0;
                            sendChatMsg(client[j], &smsgoff[j], &smsgs[j], &stclose);
                            if(stclose == 1) {
                                close(client[j]);
                                client[j]=-1;
                                client_name[j][0]=0;
                                smsgoff[j]=0;
                                rmsgoff[j]=0;
                                firstmsg[j]=1;
                            }
                        }
                    }
                }
            }

            /*!
             * 客户端
             */
            for(i=0; i<MAX_CLIENT; ++i) {
                if(client[i] < 0) continue;
                if(FD_ISSET(client[i], &rfds)) {
                    /*!
                     * 该客户端可以读，有数据到来
                     */
                    //非阻塞模式下尽可能的最大读取数据
                    for(;;) {
                        readed = recv(client[i], (char*)&rmsgs[i] + rmsgoff[i], sizeof(nb_chatmsg_t) - rmsgoff[i], 0);
                        if(readed == -1) {
                            if(errno == EAGAIN) {
                                //没有更多数据可读
                                break;
                            }
                        } else if(readed == 0) {
                            /*!客户端关闭了*/
                            close(client[i]);
                            client[i] = -1;
                            client_name[i][0]=0;
                            smsgoff[i]=0;
                            rmsgoff[i]=0;
                            firstmsg[i]=0;
                        } else {
                            /*!有数据可读*/
                            rmsgoff[i] += readed;
                            rmsgoff[i] %= nbChatMsgLen;
                            /*!接收了一个完整的数据*/
                            if(rmsgoff[i] == 0) {
                                /*根据数据的指向，发送过去*/
                                if(firstmsg[i] && strlen(rmsgs[i].m_from) > 0) {
                                    memset(&client_name[i], 0, sizeof(client_name));
                                    strncpy(client_name[i], rmsgs[i].m_from, sizeof(client_name[i])-1);
                                    firstmsg[i]=0;
                                }
                                printf("接收一个数据包,来自%s, 发送给:%s，内容:%s\n", rmsgs[i].m_from, rmsgs[i].m_to, rmsgs[i].m_msg);

                                /*检索名称，并发送给对端*/
                                if(strcmp(rmsgs[i].m_to , "all") == 0) {
                                    for(j=0; j<MAX_CLIENT; ++j) {
                                        if(client[j] < 0) continue;
                                        /*!
                                         * 上次未发送完成的数据
                                         */
                                        if(smsgoff[j] != 0) {
                                            printf("******[sendall]发送未发送完成的数据给:%s,来自:%s\n", smsgs[j].m_from, smsgs[j].m_to);
                                        } else {
                                            /*!拷贝新数据进行发送*/
                                            memcpy(&smsgs[j], &rmsgs[i], nbChatMsgLen);
                                        }
                                        stclose = 0;
                                        sendChatMsg(client[j], &smsgoff[j], &smsgs[j], &stclose);
                                        if(stclose == 1) {
                                            close(client[j]);
                                            client[j]=-1;
                                            client_name[j][0]=0;
                                            smsgoff[j]=0;
                                            rmsgoff[j]=0;
                                            firstmsg[j]=1;
                                        }
                                    }
                                } else {
                                    for(j=0; j<MAX_CLIENT; ++j) {
                                        if(strlen(client_name[j]) == 0) continue;

                                        /*!
                                         * 找到了要发送的对象
                                         */
                                        if(strcmp(client_name[j], rmsgs[i].m_to) == 0) {
                                            /*!
                                             * 上次未发送完成的数据
                                             */
                                            if(smsgoff[j] != 0) {
                                                printf("******[sendto-%s]发送未发送完成的数据给:%s,来自:%s\n", client_name[j],smsgs[j].m_from, smsgs[j].m_to);
                                            } else {
                                                /*!拷贝新数据进行发送*/
                                                memcpy(&smsgs[j], &rmsgs[i], nbChatMsgLen);
                                            }
                                            stclose = 0;
                                            sendChatMsg(client[j], &smsgoff[j], &smsgs[j], &stclose);
                                            if(stclose == 1) {
                                                close(client[j]);
                                                client[j]=-1;
                                                client_name[j][0]=0;
                                                smsgoff[j]=0;
                                                rmsgoff[j]=0;
                                                firstmsg[j]=1;
                                            }
                                            break;
                                        }
                                    } 
                                    
                                    if(j==MAX_CLIENT) {
                                        printf("没有找到用户:%s\n", rmsgs[i].m_to);
                                        for(j=0; j<MAX_CLIENT; ++j) {
                                            printf("fd=%d\tname:%s\n", client[j], client_name[j]);
                                        }
                                    }
                                }
                                break;
                             } else {
                                 printf("----接收数据,来自%d, %d (bytes)\n", client[i], readed);
                             }
                        }
                    }
                }
            }
            
        }

        maxfd = (sfd > infd) ? (sfd) : (infd);
        FD_ZERO(&rfds);
        for(i=0; i<MAX_CLIENT; ++i) {
            if(client[i] < 0) continue;
            if(client[i] > maxfd) 
                maxfd = client[i];
            FD_SET(client[i], &rfds);
        }
        FD_SET(infd, &rfds);
        FD_SET(sfd, &rfds);
        maxfd++;
        tv.tv_sec = 3;
    }

    return 0;
}
