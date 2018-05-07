/*!
 * 使用poll来监听定时器事件
 * int timerfd_create(clockid_t clockid, int flags);
 * int timerfd_settime(int fd, int flags, struct itimerspec *newvalue, struct itimerspec* oldvalue); //flags 0:相对现在的事件 TFD_TIMER_ABSTIME
 * int timerfd_gettime(int fd, struct itimerspec* curvalue);
 * int close(int fd); //使用close来关闭一个文件描述符
 *
 * TFD_TIMER_ABSTIME仅对CLOCK_REALTIME相匹配，因为MONOTONIC是个单调时间，无法计算绝对时间
 * 只能是通过两个单调时间差来计算时间的间隔
 */

#include <sys/poll.h>
#include <sys/timerfd.h>
#include <sys/types.h>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <memory.h>
#include <stdint.h> //uint8_t int8_t utin32_t int32_t int64_t uint64_t

static const unsigned MAX_POLLFD=100;
static uint64_t totalExpires ;

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
    struct pollfd pfd[MAX_POLLFD];
    int i,j, n;
    int tfd[3];
    char *s;
    uint64_t numExpires;
    clockid_t tfdclock[] = {CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_REALTIME };
    struct itimerspec its[3];

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
    //tfd[0] = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
    //tfd[1] = timerfd_create(CLOCL_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
    //tfd[2] = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);

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
    its[2].it_value.tv_sec = time(NULL)-10; 
    its[2].it_interval.tv_sec = 5;
    if(timerfd_settime(tfd[2], TFD_TIMER_ABSTIME, &its[2], NULL) < 0) {
        for(i=0; i<3; ++i) close(tfd[i]);
        perror("timerfd_settime");
        return 1;
    }
    
    /*!
     * 将描述符增加到struct pollfd*/
    for(i=0; i<3; ++i) {
        pfd[i].fd = tfd[i];
        pfd[i].events = POLLIN;
    }

    for(;;) {
        n = poll(pfd, MAX_POLLFD, -1);
        if(n < 0) {
            if(errno == EINTR || errno == EWOULDBLOCK) continue;
            perror("poll ");
            return 1;
        } 

        for(i=0; i<MAX_POLLFD; ++i) {
            if(pfd[i].fd < 0) continue;

            /*!如果不含POLLIN事件，则认为没有数据到达*/
            if(!(pfd[i].revents & POLLIN)) continue;
            /*!从文件描述符中读取超时的次数*/
redo:
            j = read(pfd[i].fd, &numExpires, sizeof(numExpires));
            if(j < 0) {
                if(errno == EINTR || errno == EWOULDBLOCK) {
                    goto redo;
                }
                perror("read");
                return 1;
            }

            if(j != sizeof(numExpires)) {
                perror("read wrong numExpires");
                return 1;
            }

            if(pfd[i].fd == tfd[0]) {
                s = "tfd[0]";
            } else if(pfd[i].fd == tfd[1]) {
                s = "tfd[1]";
            } else if(pfd[i].fd == tfd[2]) {
                s = "tfd[2]";
            } else {
                s = "tfd_unkown";
            }

            /*!注意，别写错了,读取的是numExpires*/
            showTime(s, numExpires);
        }
    }

    for(i=0; i<3; ++i) close(tfd[i]);
    return 0;
}


