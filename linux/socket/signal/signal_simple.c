/*!
 * 简单的信号驱动,信号驱动是边缘触发
 * 1.设置信号的处理，必须在设置文件的属性之前
 *   sigaction(....)，如果采用信号队列的方式（实时信号）
 *   则需要设置文件描述符的实时信号
 *   sigaction(SIGIO, ..);这种方式信号通知不会排队
 * 2.设置文件属性
 *   (1)设置描述符的属主（属主用来接收信号)F_SETOWN, F_GETOWN, F_SETOWN_EX, F_SETOWN_EX
 *   (2)设置描述符的标志位O_ASYNC
 * 3.在信号处理中设置标志位，（非队列信号的标准处理方式)
 */

#define _GNU_SOURCE

#include <sys/select.h> //用来做定时器
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h> //STDIN_FILENO
#include <fcntl.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

static volatile sig_atomic_t gotSigIO;

void
sigio_handler(int sig) {
    /*!设置获取信号的标志位*/
    gotSigIO = 1;
}

void setTimeVal(struct timeval* tv) {
    if(!tv) return ;
    tv->tv_sec = 0;
    tv->tv_usec = 1000*500; //0.5s
}

int
main() {
    int n, bufPos, readed, i;
    char buf[512];
    char line[1024];
    struct timeval tv;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = sigio_handler;

    /*!
     * 设置信号的处理函数，要在fcntl之前
     */
    if(sigaction(SIGIO, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    /*!
     * 设置文件描述符的属主
     */
    if(fcntl(STDIN_FILENO, F_SETOWN, getpid()) < 0) {
        perror("fcntl ");
        return 1;
    }

    /*!
     * 设置文件描述符的标志位
     */
    if(fcntl(STDIN_FILENO, F_SETFL, O_ASYNC) < 0) {
        perror("fcntl ");
        return 1;
    }

    /*!
     * 将STDIN设置为非阻塞，在边缘触发模式下使用
     * 非边缘模式，（水平模式，select, pselect, poll, ppoll)不可使用
     * select,poll均是采用非阻塞来判断fd可用
     */
    //这里设置为非阻塞，接收不到信号变化,WHY?????
    /*if(fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }*/

    /*!
     * 使用select来阻塞延时，避免比较gotSigIO频率太快
     * 而导致过高的CPU占用
     */
    bufPos=0;
    setTimeVal(&tv);
    memset(buf, 0,sizeof(buf));

    for(;;) {
        n= select(0, NULL, NULL, NULL, &tv);
        if(n < 0) {
            perror("select ");
        } else if(n == 0) {
            /*!超时，这是我们想要的*/
            if(gotSigIO) {
                /*!尽可能的从STDIN_FILENO中读取数据*/
                printf("gotSigIO");
                for(;;) {
                    readed = read(STDIN_FILENO, buf, sizeof(buf));
                    if(readed == -1 ) {
                        if(errno == EAGAIN) {
                            gotSigIO = 0;
                            break;
                        }
                        perror("read ");
                        exit(1);
                    } else {
                        for(i=0;bufPos < sizeof(line);) {
                            if(buf[i] == '\n') buf[i]=0;
                            line[bufPos++] = buf[i];
                            if(buf[i] == 0) {
                                printf("line:%s\n", line);
                                bufPos=0;
                                break;
                            }
                            i++;
                        } 

                        if(bufPos == sizeof(line)){
                            line[sizeof(line)-1]=0;
                            printf("line=%s\n", line);
                            bufPos=0;
                        }
                    }
                }
            }
        } else {
            assert(0);
        }

        setTimeVal(&tv);
    }
    return 0;
}


