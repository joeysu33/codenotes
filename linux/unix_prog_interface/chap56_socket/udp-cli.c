/*
 * udp-client
 * 使用connect来绑定inet地址，可以不需要
 * 在recvfrom和sendto的时候指定接收地址
 */

#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp-comm.h"

int
main(int argc, char* argv[])  {
    int fd;
    int i, nWritten, nReaded;
    struct sockaddr_in addr;
    char buf[1024];

    if(argc < 2) {
        printf("%s <data>...\n", argv[0]);
        return 1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd == -1) {
        perror("socket ");
        return 2;
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;

    /*
     * 可以给客户端本地指定一个端口
     * 小于65536，这样本地的端口就被限定了
     */
    addr.sin_port = htons(54321);
    if(bind(fd, (const struct sockaddr*)&addr, sizeof(addr)) == -1) {
        close(fd);
        perror("bind ");
        return 1;
    }

    /*!
     * 内核会记录该socket所对应的对端socket信息，直接进行读写
     * 连接上去之后就可以直接读写了,连接到服务器，
     * 端口改为服务器的
     */
    addr.sin_port = htons(sc_port);
    if(connect(fd, (const struct sockaddr*)&addr, sizeof(addr)) == -1) {
        close(fd);
        perror("bind ");
        return 3;
    }

    /*!
     * 这里假定发送的数据都比较小，不考虑底层拆包的问题
     * 真实场景，必须要定制socket的数据包格式，否则可能
     * 会无法给数据画界，也就是“粘包”
     */
    for(i=1; i<argc; ++i) {
        nWritten = write(fd, argv[i], strlen(argv[i]));
        if(nWritten < 0) {
            close(fd);
            perror("write ");
            return 4;
        }else if(nWritten==0) {
            close(fd);
            perror("nWriten == 0 ");
            return 5;
        } else {
            printf("write:%s, size=%d\n", argv[i], nWritten);
            nReaded = read(fd, buf, sizeof(buf));
            if(nReaded < 0) {
                close(fd);
                perror("read ");
                return 6;
            } else {
                buf[nReaded] = 0;
                printf("read:%s\n", buf);
            }
        }
    }

    /*!
     * close server
     */
    if(write(fd, "exit", 4) < 0) {
        close(fd);
        perror("write ");
        return 6;
    }

    close(fd);
    return 0;
}

