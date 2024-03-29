/*!
 * 使用select函数来实现I/O复用,select一般支持1024左右，实际的值是FD_SETSIZE
 * select(或pselect)和poll(或ppoll)，判断可读写的条件都是socket非阻塞
 *
 * 文件描述符边界:
 * 特别注意:在Linux上FD_SETSIZE是对一个值的边界进行限制，也就是说如果我事先构建了
 * 1025个文件描述符(加入FD_SETSIZE是1024)的话，那么1025的描述符是不会处理的
 * tv可能会修改
 *
 * 实际内核支持的更多
 * int select(int nfds, fd_set *readfd, fd_set* writefd, fd_set* exceptfd,
 *          struct timeval* timeout);
 * nfds:表示readfd,writefd和exceptfd中最大FD+1，这样内核可以快速的检测边界，把不符合条件的
 * 文件描述符直接过滤掉
 * exceptfd:有两种情况发生
 * 1.流式数据有带外数据(Urgent Data MSG_OOB) Out of Bound
 * 2.
 *
 * return:
 * 0:超时
 * -1:错误，错误类型EBADF,不合法的描述符 EINVAL,不合法的参数, EINTR，接收到中断信号, ENOMEM,没有足够的内存
 * select每次都需要重新设置
 * socket recv返回0表示，对端的socket已经关闭了
 *
 *  FD_ZERO(fd_set* s);
 *  FD_SET(int fd, fd_set* s);
 *  FD_CLR(int fd, fd_set* s);
 *  FD_ISSET(int fd, fd_set* s);
 *
 *  =======I/O多路复用表========
 *  select/poll 水平触发
 *  signal I/O  边缘触发
 *  epolll      水平触发、边缘触发
 *
 * 本例子实现一个chatroom的服务端，可以让服务端和客户端之间进行聊天
 * 客户端将所有的数据传送到服务器，服务器将所有的信息分发给其他客户端
 * 如果监听可写，则非常占用CPU资源，因为只要对方有接收数据，本段就始终能写
 */

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h> //support select
#include <sys/time.h>  //support struct timeval
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <arpa/inet.h> //inet_addr
#include <netinet/in.h> //struct sockaddr
#include <memory.h>
#include <assert.h>
#include <errno.h>
#include "msg.h"


#define MAX_CLINET 10
#define BACKLOG 5
#define QUEUE_SIZE 20
#define LISTEN_WR
//#define ENABLE_NONBLOCK

void 
maxSupport() {
    printf("select最大支持的(FD_SETSIZE): %d\n", FD_SETSIZE);
}

/*!每个客户端收发的数据*/
static chatmsg_t csmsg[MAX_CLINET];
static chatmsg_t crmsg[MAX_CLINET];
static int client[MAX_CLINET];
static int sendoff[MAX_CLINET];
static int recvoff[MAX_CLINET];
static chatmsg_t msgQueue[QUEUE_SIZE];
static int msgQueueIndex;
/*!
 * 每个客户端自己记录发送的消息索引，所有
 * 要发送的消息均来自消息队列
 * (clientMsgIndex+1) !=  msgQueue
 * clientMsgIndex++;
 * clientMsgIndex %= QUEUE_SIZE
 */
static int clientMsgIndex[MAX_CLINET];

int
getClientIndex(int fd) {
    int i;
    for(i=0; i<MAX_CLINET; ++i) {
        if(client[i] < 0) continue;
        if(client[i] == fd) return i;
    }

    assert(0);
    return -1;
}
/*!
 * 从数据流中接收一个完整的消息
 */
void
recvChatMsg(int fd, chatmsg_t* msg) {
    int index = getClientIndex(fd);
    ssize_t n = recv(fd, (char*)msg+recvoff[index], chatMsgLen-recvoff[index], 0);
    if(n < 0) {
        perror("recv ");
        exit(1);
    }else if(n==0) {
        printf("close client:%d\n",fd);
        client[index]=-1;
    } else{
        recvoff[index] += n;
        recvoff[index] %= chatMsgLen;
        /*!
         * 确定已经接收了一个完整的数据
         * 将该数据放到队列
         */
        //printf("received from:%d ,data=%d (bytes)\n", fd, n);
        if(recvoff[index] == 0) {
            msg->m_extra = fd;
            memcpy(&msgQueue[msgQueueIndex], msg, chatMsgLen);
            printf("接收到了一个完整的消息，来自:%s,内容:%s, FD=%d\n", msgQueue[msgQueueIndex].m_name, msgQueue[msgQueueIndex].m_msg, fd);
            /*!
             * 数组循环队列*/
            msgQueueIndex++;
            msgQueueIndex %= QUEUE_SIZE;
            memset(msg, 0, chatMsgLen);
        } else {
            printf("----收到数据:%ld,来自:%d\n", n,fd);
        }
    }
}

/*!
 * 将一条消息完整的发送到数据流
 */
void 
sendChatMsg(int fd, const chatmsg_t* msg) {
    int index = getClientIndex(fd);
    ssize_t n;
    
    n= send(fd, (char*)msg+sendoff[index], chatMsgLen-sendoff[index], 0) ;
    if(n < 0) {
        perror("send ");
        exit(1);
    } else if(n==0) {
        perror("send0 ");
        exit(1);
    }else {
        sendoff[index] += n;
        sendoff[index] %= chatMsgLen;
        /*
         * 确定已经发送了一个完整的数据
         */
        //printf("send to:%d, data=%d (bytes)\n", fd, n);
        if(sendoff[index] == 0) {
            printf("发送了一个完整的消息给:%d, 消息来自:%s, 消息内容:%s\n", fd, msg->m_name, msg->m_msg);
            /*!将该客户端的消息指向下一个*/
            //clientMsgIndex[index]++;
        } else {
            printf("---发送数据:%ld,给:%d\n", n, fd);
        }
    }
}

int
main(int argc, char* argv[]) {
    int sfd, maxfd, n, i,j;
    struct sockaddr_in saddr, caddr;
    socklen_t caddrLen;
    fd_set wfds, rfds;
    struct timeval tv;

    //1 second
    tv.tv_sec = 30;
    tv.tv_usec = 0;

    /*!默认未连接的都是-1*/
    for(i=0; i<MAX_CLINET; ++i) client[i]=-1;
    for(i=0; i<MAX_CLINET; ++i) clientMsgIndex[i]=-1;
    maxSupport();
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1) {
        perror("socket ");
        return 1;
    }

    /*!
     * 将server的socket设置为非阻塞*/
#if defined(ENABLE_NONBLOCK)
    if(fcntl(sfd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl ");
        return 1;
    }
#endif

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
        perror("bind ");
        return 1;
    }

    if(listen(sfd, BACKLOG) == -1) {
        perror("listen ");
        return 1;
    }

    /*!初始化fd_set */
    FD_ZERO(&wfds);
    FD_ZERO(&rfds);

    FD_SET(sfd, &rfds);
    maxfd = sfd+1;
    for(;;) {
#if defined(LISTEN_WR)
        n = select(maxfd, &rfds, &wfds, NULL, &tv);
#else
        //因为监听可写基本不阻塞，所以导致非常消耗CPU，故只监听可读
        n = select(maxfd, &rfds, NULL, NULL, &tv);
#endif
        if(n < 0) {
            perror("select ");
            return 2;
        }else if(n==0) {
            printf("select超时...\n");
        } else {
            /*!新的连接*/
            if(FD_ISSET(sfd, &rfds)) {
                for(i=0; i<MAX_CLINET; ++i) {
                    if(client[i] < 0) break;
                }
                /*!
                 * 还有可用的客户端连接描述符
                 * caddrLen是一个value-and-result既是输入又是输出*/
                caddrLen = sizeof(struct sockaddr_in);
                if(i != MAX_CLINET) {
                    /*!在接收socket之后，直接将对等socekt设置为非阻塞，注意这里的标志位是SOCK_NONBLOCK，如果是fcntl的话是O_NONBLOCK*/
#if defined(ENABLE_NONBLOCK)
                    client[i] = accept4(sfd, (struct sockaddr*)&caddr, &caddrLen, SOCK_NONBLOCK);
#else
                    client[i] = accept4(sfd, (struct sockaddr*)&caddr, &caddrLen, 0);
#endif
                    if(client[i] == -1) {
                        perror("accept4 ");
                        return 1;
                    }
                    printf("接收到新客户端:%d\n", client[i]);
                }
            } 

            /*!已经建立的连接*/
            for(i=0; i<MAX_CLINET; ++i) {
                if(client[i] < 0) continue;
                /*!
                 * 连接可读
                 */
                if(FD_ISSET(client[i], &rfds)) {
                    printf("从客户端接收到数据:%d\n", client[i]);
                    recvChatMsg(client[i], &crmsg[i]);

#if !defined(LISTEN_WR)
                    for(j=0; j<MAX_CLINET; ++j) {
                        if(client[j] < 0) continue;
                        if(j == i) continue;
                        memcpy(&csmsg[j], &crmsg[i], sizeof(chatmsg_t));
                        sendChatMsg(client[i], &csmsg[j]);
                    }
#endif
                } 

#if defined(LISTEN_WR)
                if(FD_ISSET(client[i], &wfds)) {
                    //printf("可以将数据写入到客户:%d\n", client[i]);
                    //for(i=j; i<MAX_CLINET; ++j) {
                        /*!
                         * 该消息队列中存在可以发送的数据
                         * 如果有的消息阻塞太慢可能会丢失数据（循环队列)
                         * 仅发送不是来自客户端自己的消息
                         */
                        //无任何消息可以发送
                        if(((clientMsgIndex[i]+1) % QUEUE_SIZE) == msgQueueIndex) {
                            continue;
                        }

                        clientMsgIndex[i]++;
                        clientMsgIndex[i] %= QUEUE_SIZE;

                        for(;;) {
                            if(msgQueue[clientMsgIndex[i]].m_extra != client[i]) {
                                memcpy(&csmsg[i], &msgQueue[clientMsgIndex[i]], sizeof(chatmsg_t));
                                assert(strlen(csmsg[i].m_name) > 0);
                                sendChatMsg(client[i], &csmsg[i]);
                                if(((clientMsgIndex[i]+1) % QUEUE_SIZE) != msgQueueIndex) {
                                     clientMsgIndex[i]++;
                                } else {
                                    break;
                                }
                            } else {
                               if(((clientMsgIndex[i]+1) % QUEUE_SIZE) == msgQueueIndex) {
                                   break;
                               } else {
                                  clientMsgIndex[i]++;
                                  clientMsgIndex[i] %= QUEUE_SIZE;
                               }
                            }
                       }

                        /*if(((clientMsgIndex[i]+1) % QUEUE_SIZE) != msgQueueIndex) {
                            printf("clientMsgIndex[%d]=%d, msgQueueIndex=%d\n", i,clientMsgIndex[i], msgQueueIndex);
                            memcpy(&csmsg[i], &msgQueue[clientMsgIndex[i]], sizeof(chatmsg_t));
                            assert(strlen(csmsg[i].m_name) > 0);
                            sendChatMsg(client[i], &csmsg[i]);
                        } */
                    //}
                }
#endif
            }

        }
        /*!重新组织fd_set*/
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        maxfd = sfd;
        for(i=0; i<MAX_CLINET; ++i) {
            if(client[i] < 0) continue;
            if(maxfd < client[i]) {
                maxfd = client[i];
            }
            FD_SET(client[i], &rfds);
            FD_SET(client[i], &wfds);
        }

        FD_SET(sfd, &rfds);
        maxfd++;
        tv.tv_sec = 30;
        tv.tv_usec = 0;

    }

    return 0;
}




