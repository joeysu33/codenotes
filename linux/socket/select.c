/*!
 * 使用select函数来实现I/O复用,select一般支持1024左右，实际的值是FD_SETSIZE
 *
 * 文件描述符边界:
 * 特别注意:在Linux上FD_SETSIZE是对一个值的边界进行限制，也就是说如果我事先构建了
 * 1025个文件描述符(加入FD_SETSIZE是1024)的话，那么1025的描述符是不会处理的
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
 * -1:错误
 * select每次都需要重新设置
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
 * 在使用IO多路复用的时候，一定要将socket设置为O_NONBLOCK，这样避免在操作socket的时候造成阻塞
 * 阻塞应该在select/poll的IO多路复用上发生
 *
 * 本例子实现一个chatroom的服务端，可以让服务端和客户端之间进行聊天
 * 客户端将所有的数据传送到服务器，服务器将所有的信息分发给其他客户端
 */

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h> //support select
#include <sys/time.h>  //support struct timeval
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h> //inet_addr
#include <netinet/in.h> //struct sockaddr
#include <memory.h>
#include <assert.h>
#include <errno.h>
#include "msg.h"


#define MAX_CLINET 10
#define PORT 8888
#define BACKLOG 5
#define QUEUE_SIZE 20

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
    int n = recv(fd, (char*)msg+recvoff[index], chatMsgLen-recvoff[index], 0);
    if(n <= 0) {
        perror("recv ");
        exit(1);
    }else {
        recvoff[index] += n;
        recvoff[index] %= chatMsgLen;
        /*!
         * 确定已经接收了一个完整的数据
         * 将该数据放到队列
         */
        printf("received from:%d ,data=%d (bytes)\n", fd, n);
        if(recvoff[index] == 0) {
            memcpy(&msgQueue[msgQueueIndex], msg, chatMsgLen);
            printf("接收到了一个完整的消息，来自:%s,内容:%s, FD=%d\n", msg->m_name, msg->m_msg, fd);
            /*!
             * 数组循环队列*/
            msgQueueIndex++;
            msgQueueIndex %= QUEUE_SIZE;
            memset(msg, 0, chatMsgLen);
        }
    }
}

/*!
 * 将一条消息完整的发送到数据流
 */
void 
sendChatMsg(int fd, const chatmsg_t* msg) {
    int index = getClientIndex(fd);
    int n= send(fd, (char*)msg+sendoff[index], chatMsgLen-sendoff[index], 0) ;
    if(n <= 0) {
        perror("send ");
        exit(1);
    } else {
        sendoff[index] += n;
        sendoff[index] %= chatMsgLen;
        /*
         * 确定已经发送了一个完整的数据
         */
        printf("send to:%d, data=%d (bytes)\n", fd, n);
        if(sendoff[index] == 0) {
            printf("发送了一个完整的消息给:%d, 消息来自:%s, 消息内容:%s\n", fd, msg->m_name, msg->m_msg);
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

    tv.tv_sec = 1;
    tv.tv_usec = 0;

    /*!默认未连接的都是-1*/
    for(i=0; i<MAX_CLINET; ++i) client[i]=-1;
    maxSupport();
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sfd == -1) {
        perror("socket ");
        return 1;
    }

    /*!
     * 将server的socket设置为非阻塞*/
    if(fcntl(sfd, F_SETFL, O_NONBLOCK) == -1) {
        perror("fcntl ");
        return 1;
    }

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
        n = select(maxfd, &rfds, &wfds, NULL, &tv);
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
                    client[i] = accept4(sfd, (struct sockaddr*)&caddr, &caddrLen, SOCK_NONBLOCK);
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
                } else if(FD_ISSET(client[i], &wfds)) {
                    printf("可以将数据写入到客户:%d\n", client[i]);
                    sendChatMsg(client[i], &csmsg[i]);
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
        }
    }

    return 0;
}




