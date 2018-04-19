/*!
 * udp server
 * 监听端口数据，udp也可以直接connect
 * 这样就可以不需要调用sendto或者recvfrom来指定端口了，
 * 调用bind之后，内核会记录socket的对等socket，
 * 这样可以按照文件的样式，直接write或者read进行读写
 *
 * 客户端直接绑定即可read/write
 * 服务端不行，服务端需要有对端地址(端口)
 * 服务端必须要sento recvfrom，否则无法区分过来的客户端
 *
 * 严重警告:
 * 1.绑定地址的时候需要注意三要素 1:IP地址 2:端口 3:地址协议
 * 2.从socket上获取对端socket地址的时候，必须而且一定要注意，先
 *   给socket的地址长度赋值
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h> //sock_addr
#include <arpa/inet.h>  //inet_addr

#include "udp-comm.h"


void dumpSockAddrIn(struct sockaddr_in * addr) {
    if(!addr) return ;
    printf("AFINET=%d, address-family:%d\n", AF_INET, addr->sin_family);
    printf("address:%s\n", inet_ntoa(addr->sin_addr));
    printf("port:%d\n", ntohs(addr->sin_port));
    printf("\n");
}

int
main() {
    int i, nReaded, nWritten;
    int fd;
    socklen_t socklen;
    struct sockaddr_in addr, caddr;
    char buf[1024];
    const char *ipaddr = "127.0.0.1";

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0) {
        perror("socket ");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ipaddr);
    addr.sin_port = htons(sc_port);
    if(bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(fd);
        perror("bind ");
        return 2;
    }

    memset(buf, 0, sizeof(buf));

    while(1) {
        /*!
         * 严重警告
         * 如果要获取对端的socket地址，这里必须要初始化socket的地址长度
         * 否则会无法读取对端的socket地址
         */
        socklen=sizeof(caddr);
        memset(&caddr, 0, sizeof(caddr));
        nReaded = recvfrom(fd, buf, sizeof(buf)-1, 0, (struct sockaddr*)&caddr, &socklen);
        if(socklen != sizeof(struct sockaddr_in)) {
            close(fd);
            printf("socklen=%d,siezof(sockaddr_in)=%ld ", socklen, sizeof(struct sockaddr_in));
            return 1;
        }

        if(nReaded < 0) {
            close(fd);
            perror("recvfrom ");
            return 3;
        } else if (nReaded == 0) {
            close(fd);
            perror("nReaded == 0 ");
            return 4;
        } else {
            dumpSockAddrIn(&caddr);
            buf[nReaded]=0;
            printf("receice: %s\n", buf);
            if(strcmp(buf, "exit") == 0) {
                printf("recieve exit!!!\n");
                close(fd);
                break;
            }

            for(i=0; i<nReaded; ++i) buf[i]=toupper(buf[i]);
            nWritten = sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&caddr, socklen);
            if(nWritten < 0) {
                close(fd);
                perror("sendto ");
                return 5;
            } else if(nWritten == 0) {
                close(fd);
                perror("nWritten == 0 ");
                return 6;
            } else {
                printf("send: %s\n", buf);
            }
        }
    }
    
    return 0;
}


