/*!
 * 简单的select，采用非阻塞模式测试
 */

#include <sys/socket.h>
#include <sys/select.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int
main() {
    fd_set rfds;
    struct timeval tv;
    int n, maxfd, readed, pos;
    int i,j;
    char line[16];
    char buf[8];
    
    /*!
     * 检测是否包含标准输入，终端
     */
    if(fcntl(STDIN_FILENO, F_GETFL, 0) < 0) {
        perror("fcntl ");
        return 1;
    }

    /*!
     * 非阻塞的读取
     */
    if(fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }

    if(setvbuf(stdin, NULL, _IONBF, 0) != 0) {
        perror("setvbuf ");
        return 1;
    }

    tv.tv_sec = 3;
    maxfd = STDIN_FILENO + 1;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);

    pos=0;
    for(;; ) {
        n = select(maxfd, &rfds, NULL, NULL, &tv);
        if(n < 0) {
            perror("select ");
            return 1;
        } else if(n == 0) {
            printf("timeout ...\n");
        } else {
            for(;;) {
                readed = read(STDIN_FILENO, buf, sizeof(buf));
                if(readed == -1) {
                    if(errno = EAGAIN) {
                        printf("无数据可读\n");
                        break;
                    } else {
                        perror("read ");
                        exit(1);
                    }
                } else if(readed == 0) {
                    perror("readed == 0 ");
                    exit(2);
                } else {
                    for(i=0; i< readed; ++i) {
                        /*!
                         * 达到了一行数据的上限
                         */
                        if(pos == (sizeof(line)-1)) {
                            line[pos-1]=0;
                            printf("line-max=%s\n", line);
                            pos=0;
                            break;
                        }

                        if(buf[i] == '\n') {
                            buf[i]=0;
                            line[pos++]=0;
                            printf("line:%s\n", line);
                            pos=0;
                            break;
                        } else {
                            line[pos++] = buf[i];
                        }

                    }
                }
            }
        }

        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 3;
    }
    return 0;
}
