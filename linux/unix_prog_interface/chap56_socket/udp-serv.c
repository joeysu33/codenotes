/*!
 * udp server
 * 监听端口数据，udp也可以直接connect
 * 这样就可以不需要调用sendto或者recvfrom来指定端口了，
 * 调用connect之后，内核会记录socket的对等socket，
 * 这样可以按照文件的样式，直接write或者read进行读写
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h> //sock_addr
#include <arpa/inet.h>  //inet_addr


const int sc_port = 8888;

int
main() {
    int fd, cfd, socklen;
    struct sockaddr_in addr, caddr;
    char buf[16];
    const char *ipaddr = "127.0.0.1";

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0) {
        perror("socket ");
        return 1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ipaddr);
    //inet_pton(AF_INET, ipaddr, &addr.sin_addr);
    addr.sin_port = htons(sc_port);
    if(bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind ");
        return 2;
    }

    socklen=0;
    memset(buf, 0, sizeof(buf));
    /*if(recvfrom(fd, buf, sizeof(buf)-1, 0, (struct sockaddr*)&caddr, &socklen) < 0) {
        perror("recvfrom ");
        return 3;
    }
    */
    if(read(fd, buf, sizeof(buf)-1) < 0) {
        perror("read ");
        return 33;
    }

    printf("receice: %s\n", buf);
    strcpy(buf, "udp-server");
    /*
    cfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(cfd < 0) {
        perror("socket ");
        return 4;
    }
    */

    /*!
     * 将socket绑定到一个地址之后，直接使用
     * write和read来进行操作
     */
    /*if(connect(fd, (const struct sockaddr*)&caddr, socklen) < 0) {
        perror("connect ");
        return 5;
    }
    */

    /*! write不可以，客户端可以直接connect过去，服务端必须sendto和recvfrom
     * 因为传输的时候需要传输地址
     */
    if(write(fd, buf, strlen(buf)) < 0) {
        perror("write ");
        return 6;
    }

    //close(cfd);
    close(fd);
    return 0;
}


