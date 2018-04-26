/*!
 * 针对select编写的chatroom
 * 所编写的客户端,客户端可以向服务器发送数据
 * 只接收来自服务器中其他人发送的消息
 * 因为大部分情况始终可写，所以会导致CPU的占用非常高
 * select调用立即返回
 */

#include <unistd.h>  //STDIN_FILENO STDOUT_FILENO STDERR_FILENO
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h> //select
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>  //inet_addr
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include "msg.h"

#define MAX_LINE MSG_SIZE

static char name[20];
static int recvoff;
static int sendoff;
static char buf[MAX_LINE];
static chatmsg_t sndMsg;
static chatmsg_t rcvMsg;
static char haveData;

void
recvChatMsg(int fd, chatmsg_t* msg) {
    ssize_t n;
    n = recv(fd, (char*)msg+recvoff, chatMsgLen-recvoff, 0);
    if(n < 0) {
        perror("recv ");
        exit(200);
    } else if(n==0){ 
        perror("recv 0");
        exit(100);
    } else {
        recvoff += n;
        recvoff %= chatMsgLen;
        /*!
         * 接收到了一个完整的数据包
         */
        if(recvoff == 0) {
            printf("%s:接收到了来自:%s，内容:%s\n", name, msg->m_name, msg->m_msg);
            memset(msg, 0, sizeof(chatmsg_t));
        } else {
            printf("---收到数据:%ld\n", n);
        }
    }
}

void
sendChatMsg(int fd, chatmsg_t* msg) {
    ssize_t n;
    /*!可能msg并未发送完成*/
    if(!haveData) return ;
    memcpy(&msg->m_msg, buf, sizeof(buf));
    memcpy(&msg->m_name, name, sizeof(name));
    memset(buf, 0, sizeof(buf));
    haveData = 0;
    n = send(fd, (char*)msg+sendoff, chatMsgLen-sendoff, 0);
    if(n < 0) {
        perror("send ");
        exit(2);
    } else if(n==0) {
        perror("send 0");
        exit(100);
    } else{
        sendoff += n;
        sendoff %= chatMsgLen;
        /*!发送完成一个完整的数据*/
        if(sendoff == 0) {
            printf("%s:发送了一个完整的数据:%s\n", msg->m_name, msg->m_msg);
            memset(msg, 0, sizeof(chatmsg_t));
        } else {
            printf("----发送数据:%ld\n", n);
        }
    }
}


void 
readLine(int fd) {
    int i;
    char buffer[512];
    char *cp = buf, *endp = buf+sizeof(buf), *cp2 = buffer;
    ssize_t readed ;

    /*!
     * 有数据暂时不读
     */
    if(haveData) return ;
    readed = read(fd, buffer, sizeof(buffer));
    if(readed < 0) {
        perror("read ");
        exit(1);
    }else if(readed == 0) {
        return ;
    }

    for(cp ;cp < endp; ++cp) {
        if(!*cp) {
            break;
        }
    }
    /*!
     * 数据已经写满还没有见到\n"
     */
    if(cp == endp) {
        --cp;
        *cp = 0;
        haveData = 1;
    } else {
        for(; cp != endp && readed > 0; ++cp2, ++cp,--readed) {
            if(*cp2 == '\n') {
                *cp = 0;
                break;
            } else {
                *cp = *cp2;
            }
        }
        if(cp == endp) {
            --cp;
            *cp = 0;
        }
        haveData = 1;
    }

}

void
set1sec(struct timeval* tv) {
    tv->tv_sec = 30;
    tv->tv_usec = 0;
}

int
main(int argc, char* argv[]) {
    int fd,maxfd, i,n;
    struct sockaddr_in addr, servAddr;
    fd_set wfds, rfds;
    struct timeval tv;

    if(argc < 2) {
        perror("输入用户名...");
        return 100;
    }

    /*
     * copy most first n bytes to dest
     */
    strncpy(name,argv[1], sizeof(name)-1);
    if(setvbuf(stdout, NULL, _IONBF, 0) != 0) {
        perror("setvbuf ");
        return 10;
    }

    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(fd < 0) {
        perror("socket");
        return 1;
    }

    /*
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(6666);
    addr.sin_family = AF_INET;

    if(bind(fd, (const struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind ");
        return 2;
    }
    */

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);

    /*!
     * ***特别注意:socket可以自发自收，在同一个端口上
     */
    if(connect(fd, (const struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("connect ");
        return 3;
    }

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_SET(STDIN_FILENO, &rfds);
    FD_SET(fd, &rfds);
    FD_SET(fd, &wfds);
    maxfd = fd+1; //STDIN_FILENO=0

    set1sec(&tv);
    for(;; ) {
        //优化
        //n= select(maxfd, &rfds, &wfds, NULL, &tv);
        n= select(maxfd, &rfds, NULL, NULL, &tv);
        if(n < 0) {
            perror("select ");
            return 4;
        } else if(n == 0) {
            printf("超时...\n");
        } else {
            if(FD_ISSET(fd, &rfds)) {
                recvChatMsg(fd, &rcvMsg);
            }
            //为了降低CPU的资源，将发送移动到readLine中
            /*if(FD_ISSET(fd, &wfds)) {
                sendChatMsg(fd, &sndMsg);
            }*/
            if(FD_ISSET(STDIN_FILENO, &rfds)) {
                readLine(STDIN_FILENO);
                sendChatMsg(fd, &sndMsg);
            }

        }
        /*!
         * 重新组织select
         */
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_SET(STDIN_FILENO, &rfds);
        FD_SET(fd, &rfds);
        FD_SET(fd, &wfds);
        maxfd = fd+1;
        set1sec(&tv);

    }

    return 0;
}


