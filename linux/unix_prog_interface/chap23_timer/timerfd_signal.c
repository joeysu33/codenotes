/*!
 *
 * 将timerfd_poll转换为使用实时信号来获取IO事件
 * 实时信号对文件IO起作用，对timer不起作用，建议
 * 用select, poll, epoll基本对所有的都可以
 *
 */

#define _GNU_SOURCE

#include <sys/poll.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <signal.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>
#include <stdint.h> //uint8_t int8_t utin32_t int32_t int64_t uint64_t
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static const unsigned MAX_POLLFD=100;
static uint64_t totalExpires ;

void
showTime(const char* s, uint64_t expire) ;
void
sigaction_handler(int sig, siginfo_t* si, void* ucontext) {
    pid_t pid;
    ssize_t j;
    uint64_t numExpires = 0;
    char buf[32];
    /*!Unsafe in async sigIO*/
    printf("Received sig:%d, siginfo:%s", sig, strsignal(sig));
    snprintf(buf, 32, "[fd=%d]",si->si_fd);
redo:
    j = read(si->si_fd, &numExpires, sizeof(numExpires));
    if(j < 0) {
        if(errno == EINTR || errno == EWOULDBLOCK) {
            goto redo;
        }
        /*! perror > stderr,没有缓存先输出*/
        perror("read");
        exit(1);
    }

    if(j != sizeof(numExpires)) {
        //perror("read wrong numExpires");
        printf("num=%ld\n", numExpires);
        return ;
    } else {
        showTime(buf, numExpires);
    }
}

void
showTime(const char* s, uint64_t expire) {
    char buf[128];
    time_t tm;
    tm = time(NULL);

    totalExpires += expire;
    if(strftime(buf, sizeof(buf),"%Y-%m-%d %H:%M:%S", gmtime(&tm)) == 0) {
        perror("strftime ");
    }
    printf("%s: UTC:%ld localtime:%s, expires=%lu, total-expires:%lu\n", s,time(NULL), buf, expire, totalExpires);
}

int
main() {
    pid_t pid;
    struct f_owner_ex oex;
    struct sigaction sa;
    struct pollfd pfd[MAX_POLLFD];
    int i,j, n;
    int tfd[3];
    char *s;
    uint64_t numExpires;
    clockid_t tfdclock[] = {CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_REALTIME };
    struct itimerspec its[3];

    /*!初始化sigaction*/
    memset(&sa, 0, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO | SA_RESTART; //SA_RESTART not for SIGALRM
    sa.sa_sigaction = sigaction_handler;
    if(sigaction(SIGRTMIN, &sa, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    /*!
     * 初始化struct pollfd
     * 将fd设置为-1,poll会自动忽略*/
    for(i=0; i<MAX_POLLFD; ++i) {
        memset(&pfd[i], 0, sizeof(struct pollfd));
        pfd[i].fd = -1;
    }

    /*!
     * 初始化its
     */
    for(i=0; i<3; ++i) memset(&its[i], 0, sizeof(struct itimerspec));

    /*!将tfd设置为执行exec的时候关闭，而且非阻塞*/
    for(i=0; i<3; ++i) {
        tfd[i] = timerfd_create(tfdclock[i], TFD_CLOEXEC | TFD_NONBLOCK);
        if(tfd[i] < 0) {
            perror("timerfd_create");
            for(--i; i>=0; --i) {
                close(tfd[i]);
            }
            return 1;
        }
    }

    showTime("Initial", 0);
    //初始化定时器时间间隔
    its[0].it_interval.tv_sec = 1;
    its[0].it_value.tv_sec = 5;

    its[1].it_interval.tv_sec = 3;
    its[1].it_value.tv_sec = 1;

    for(i=0; i<2; ++i) 
        if(timerfd_settime(tfd[i], 0, &its[i], NULL) < 0) {
            for(i=2; i>=0; --i) close(tfd[i]);
            perror("timerfd_settime");
            return 1;
        }

    //使用绝对时间来表示,10s之后响应，应该使用CLOCK_REALTIME来构建
    //CLOCK_MONOTONIC是单调的，不会倒退
    its[2].it_value.tv_sec = time(NULL)-10;  //一上来就超时
    its[2].it_interval.tv_sec = 5;
    if(timerfd_settime(tfd[2], TFD_TIMER_ABSTIME, &its[2], NULL) < 0) {
        for(i=0; i<3; ++i) close(tfd[i]);
        perror("timerfd_settime");
        return 1;
    }
    
    //设置描述符的F_SETSIG
    oex.type = F_OWNER_PID;
    oex.pid = getpid();

    pid = getpid();
    for(i=0; i<3; ++i) {
        if(fcntl(tfd[i], F_SETSIG, SIGRTMIN) < 0) {
            perror("fcntl");
            return 1;
        }

        if(fcntl(tfd[i], F_SETFL, O_NONBLOCK | O_ASYNC) < 0) {
            perror("fcntl");
            return 1;
        }

        //if(fcntl(tfd[i], F_SETOWN_EX, &oex) < 0) {
        //    perror("fcntl");
        //    return 1;
        //}
        assert(fcntl(tfd[i], F_SETOWN, pid) != -1);
    }

    assert(fcntl(0, F_SETSIG, SIGRTMIN) != -1);
    assert(fcntl(0, F_SETFL, O_NONBLOCK | O_ASYNC) != -1);
    assert(fcntl(0, F_SETOWN, pid) != -1);

    printf("start to wait signals!\n");
    for(;;) pause();
    return 0;
}


