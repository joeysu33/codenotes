/*!
 * 简单的epoll应用
 * epoll的特点 支持边缘触发和水平触发
 * 主要函数
 * =======初始化epoll内核对象=====
 * int epoll_create(int size) ; //设置一个初始内核大小
 * int epoll_create1(int flags) ;//flags的取值:EPOLL_CLOEXEC]
 *
 * =======对epoll内核对象进行操作===
 * int epoll_ctl(int epllfd, int opt, int fd, struct epoll_event* ev); //opt的取值EPOLL_CTL_ADD, EPOLL_CTL_DEL, EPOLL_CTL_MOD
 * struct epoll_event {
 *  uint32_t events; //epoll events
 *  epoll_data_t data; //user data
 * };
 *
 * typedef union epoll_data {
 *  void*       ptr;
 *  int         fd;
 *  uint32_t    u32;
 *  uint64_t    u64;
 * } epoll_data_t;
 *
 * EPOLL_CTL_ADD :增加一个fd到epoll的intersted list中，并记录events
 * EPOLL_CTL_MOD :修改fd所关心的events
 * EPOLL_CTL_DEL :从epoll内核队列中移除fd, ev参数可以为NULL
 *
 * epoll维护两个队列
 * intersted list: 兴趣队列，所有注册的fd
 * ready list: 就绪队列,兴趣队列中已经ready的fd集合
 *
 * =========epoll等待事件========
 * int epoll_wait(int efd, struct epoll_event* ev, int maxevents, int timeout);
 * efd: epoll的描述符
 * ev:  在epoll上发生的事件集合
 * maxevents: 从ready队列中能取出的最大个数
 * timeout:  最大延时,单位ms和poll的timeout一样，与select不同,select使用struct timeval来描述超时
 *           -1:永久阻塞，直到收到ready事件
 *           0:如果没有事件,直接返回
 *           >0:在timeout内，有ready事件则返回，否则会到timeout超时为止
 */

/*!
 * 收到SIGINT信号则退出程序
 * epoll监听标准输入，如果有输入则触发，采用边缘触发模式
 */

#include <sys/epoll.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

static int timeoutCnt ;
#define MAX_EVENTS 100

void
action_handler(int sig) {
    /*! Unsafe in async signal interrput */
    printf("Caught signal:%d, timeoutCnt=%d times\n", sig, timeoutCnt);
    exit(1);
}

int
main(int argc, char* arg[]) {
    const int infd = STDIN_FILENO;
    struct sigaction  sa;
    struct epoll_event ev;
    struct epoll_event rev[MAX_EVENTS];
    int efd, n, i;
    char buf[5];
    epoll_data_t pdt;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = action_handler;

    if(sigaction(SIGINT, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    /*!
     * 将infd设置为非阻塞
     */
    if(fcntl(infd, F_SETFL, O_NONBLOCK) < 0) {
        perror("fcntl ");
        return 1;
    }

    /*!
     * 给efd设置上exec就关闭的fd标志位
     */
    efd = epoll_create1(EPOLL_CLOEXEC);
    if(efd < 0) {
        perror("epoll_create1 ");
        return 1;
    }

    /*!
     * 在epoll的intersted list中增加 ev
     * 设置infd为边缘触发
     */
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = infd;
    if(epoll_ctl(efd, EPOLL_CTL_ADD, infd, &ev) < 0) {
        perror("epoll_ctl ");
        return 1;
    }

    for(;;) {
        n = epoll_wait(efd, rev, MAX_EVENTS, 500);
        if(n < 0) {
            perror("epoll_wait ");
            exit(1);
        } else if(n == 0) {
            timeoutCnt++;
        } else if(n > 0) {
            /*!检查rev*/
            for(i=0; i<n; ++i) {
                if(rev[i].data.fd == infd) {
                    /*!从这里尽可能的读取数据*/
                    for(;;) {
                        n = read(infd, buf, sizeof(buf)-1);
                        if(n < 0) {
                            if(errno == EAGAIN) {
                                printf("No more data ...\n");
                                break;
                            }
                            perror("read ");
                            exit(1);
                        } else if(n == 0) {
                            perror("read == 0 ");
                            exit(2);
                        } else {
                            buf[n]=0;
                            printf("read=%s\n", buf);
                        }
                     }
                }
            }
        }
     }
    return 0;
}





