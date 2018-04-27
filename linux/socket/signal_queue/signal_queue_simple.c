/*!
 * 信号都是边缘触发
 * 实时信号 SIGRT开头的SIGRTMIN+1 ...
 * 使用实时信号队列的方式来实现IO复用
 * 实时信号IO和SIGIO的区别在于
 * 1.实时信号IO可以以消息队列的形式进行监听，而SIGIO只会触发一次
 * 2.实时信号IO可以在handle中来获取信号触发的原因，以及触发信号的fd
 *   SIGIO不行
 * 3.SIGIO需要的操作 
 *   -设置信号action 
 *   -给监听的fd设置F_SETOWN, O_ASYNC, O_NONBLOCK
 *   -在action handler中给信号原子值设置标记sig_atomic_t
 * 4.实时信号队列IO的操作
 *   -指定一个实时信号
 *   -设置信号action
 *   -给fd设置F_SETSIG
 *   -给struct sigaction设置SA_SIGINFO标志位
 *   -给fd设置O_NONBLOCK
 * 5.实时信号IO比SIGIO更加高效，而且更加安全(有信号队列),缺点是信号队列
 *   存在溢出的风险
 */

#define _GNU_SOURCE

#include <sys/syscall.h>
#include <sys/types.h> //gettid()
#include <signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#define gettid() syscall(__NR_gettid)

/*!
 * 使用SA_SIGINFO的标志位以后
 * 信号处理函数不是 void (*sa_handler)(int sig)
 * 而是 void (*sa_sigaction)(int, siginfo_t*, void*)
 * void* context
 * 通过getcontext来获取，一般不需要使用
 */
void
dumpSigInfo(siginfo_t* info) {
    /*!
     * si_band和revents中的掩码相同
     */
    printf("signo=%d, errno=%d, sigcode=%d\n",
            info->si_signo,
            info->si_errno,
            info->si_code);
    printf("pid=%d, ruid=%d, status=%d,utime=%ld, stime=%ld\n",
            info->si_pid,
            info->si_uid,
            info->si_status,
            info->si_utime,
            info->si_stime);
    printf("band=%ld, fd=%d\n", info->si_band, info->si_fd);
}

void
sigrt_action(int sig, siginfo_t* info, void* context) {
    int lastError = errno;
    assert(sig == info->si_signo);
    dumpSigInfo(info);
    errno = lastError;
}

int
main() {
    struct f_owner_ex owner;
    const int infd = STDIN_FILENO;
    int sigrt = SIGRTMIN + 1;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sa.sa_sigaction = sigrt_action;

    /*!
     * 首先设置信号处理
     */
    if(sigaction(sigrt, &sa, NULL) < 0) {
        perror("sigaction ");
        return 1;
    }

    /*!
     * 设置文件描述符的所属
     * 可以设置为相关的线程或进程
     */
    /*
     * owner.type = F_OWNER_TID;
    owner.pid = gettid();
    */
    owner.type = F_OWNER_PID;
    owner.pid = getpid();
    if(fcntl(infd, F_SETOWN_EX, &owner) < 0) {
        perror("fcntl ");
        return 1;
    }
    
    /*!
     * 设置O_ASYNC设置信号驱动IO
     */
    if(fcntl(infd, F_SETFL, O_NONBLOCK | O_ASYNC) < 0) {
        perror("fcntl ");
        return 1;
    }

    if(fcntl(infd, F_SETSIG, sigrt) < 0) {
        perror("fcntl ");
        return 1;
    }

    for(;;) pause();
    return 0;
}


