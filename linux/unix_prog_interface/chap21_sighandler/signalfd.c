/*!
 * int signalfd(int fd, sigset_t* mask, int flags);
 *
 * int fd: 创建一个signalfd的时候，指定为-1，修改的时候需要指定一个有效的signalfd
 * sigset_t* mask: 信号掩码
 * int flgas: 标志位 SFD_CLOEXEC, SFD_NONBLOCK
 *            和使用fcntl来设置一样
 *            SFD_CLOEXEC == fcntl(fd, F_SETFD, FD_CLOEXEC);
 *            SFD_NONBLOCK == fcntl(fd, F_SETFL, O_NONBLOCK);
 *
 *
 * return: 如果fd==-1返回一个新创建的sfd，否则返回有效的fd,也就是等于参数
 *         返回的文件描述符可以和select/pselect, poll/ppoll, epoll使用
 *
 * signalfd和sigwait/sigtimedwait一样可以实现同步接收信号，都需要配合
 * sigprocmask来使用(线程的话使用pthread_sigmask)，首先使用信号屏蔽码来屏蔽信号
 * 然后使用sigwait/sigtimedwait或signalfd来读取信号数据
 *
 * 通过调用read(sfd, buf, size)来读取信号的数据，一个信号数据
 * struct signalfd_siginfo {};
 * 特别要注意的是buf必须比sizeof(struct signalfd_siginfo)要大
 *
 * ==================================================================
 * 以上是将信号作为文件来处理，也可以将文件的IO操作由信号来操作
 * 1.监听SIGIO,设置SA_SIGINFO
 * 2.sigaction(SIGIO, &sa, NULL);
 * 3.给文件描述符符（要监听IO的）
 *   fcntl(fd, F_SETFL, O_NONBLOCK)
 *   fcntl(fd, F_SETSIG, SIGIO); //也可以设置为实时信号
 *   fcntl(fd, F_SETFL, O_ASYNC); //设置为异步信号
 *   fcntl(fd, F_SETOWN, ...);设置描述符的所属
 *   或者fcntl(fd, F_SETOWN_EX, ...)
 *
 * -----------------------------------------------------------------
 * signalfd和sigwait/sigtimedwait,pause()作为同步接收,其他的情况作为异步接收
 * raise(),kill(getpid(), sig)作为同步发送，外部进程触发是异步发送
 */

#include <sys/time.h>
#include <sys/signalfd.h> //signalfd
#include <sys/epoll.h>

#include <signal.h>  //sigaddset, sigemptyset, sigdelset, sigfillset, sigismember, sigprocmask
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <string.h>


#define MAX_EPOLL_SIZE 100

int
showSignalfd_SignalInfo(struct signalfd_siginfo* sifd) {
    printf("singalno:%d (%s), Errno:%d, SignalCode:%d, senderPID:%d, senderUID:%d,"
            "fd=%d, tid=%d band=%d, overrun=%d trapno=%d, "
            "\n",
            sifd->ssi_signo, strsignal(sifd->ssi_signo), 
            sifd->ssi_errno,
            sifd->ssi_code,
            sifd->ssi_pid,
            sifd->ssi_uid,

            sifd->ssi_fd,
            sifd->ssi_tid,
            sifd->ssi_band,
            sifd->ssi_overrun,
            sifd->ssi_trapno);
}

int main() {
    int sfd;
    int efd;
    int timeout, ret, readed;
    struct epoll_event ev;
    sigset_t mask, oldMask;
    struct signalfd_siginfo sifd;
    struct epoll_event rev[MAX_EPOLL_SIZE];


    //FD_?系列操作集合是第二个参数
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    sigaddset(&mask,SIGQUIT);
    sigaddset(&mask,SIGHUP);
    sigaddset(&mask,SIGTTIN);
    sigaddset(&mask,SIGTTOU);
    sigaddset(&mask,SIGTERM);

    if(sigprocmask(SIG_SETMASK, &mask, &oldMask) < 0) {
        perror("sigprocmask ");
        return 1;
    }

    /*!
     * sfd打开就设置了不阻塞，执行exec的时候关闭
     */
    sfd = signalfd(-1, &mask, SFD_CLOEXEC | SFD_NONBLOCK);
    if(sfd < 0) {
        perror("signalfd ");
        return 1;
    }
    printf("signalfd=%d\n", sfd);

    efd = epoll_create1(EPOLL_CLOEXEC);
    if(efd < 0) {
        perror("epoll_create1 ");
        close(sfd);
        return 1;
    }

    ev.events = EPOLLIN ;
    ev.data.fd = sfd;
    timeout = 1000 * 2; //2 seconds

    if(epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &ev) < 0) {
        perror("epoll_ctl ");
        close(sfd);
        close(efd);
        return 1;
    }

    for(;; ) {
        /*! epoll_wait(epoll_fd, ev, MAX_EPOLL_SIZE, timeout) */
        ret = epoll_wait(efd, rev, MAX_EPOLL_SIZE, timeout);
        if(ret < 0) {
            if(errno == EINTR) {
                continue;
            }
            perror("epoll_wait ");
            break;
        } else if(ret == 0) {
            printf("timeout ...\n");
        } else {
            readed = read(sfd, &sifd, sizeof(sifd));
            if(readed < 0) {
                perror("read ");
                break;
            } else {
                /*!默认一次已经读完，一般都没问题,否则按照数据流的要求需要多次读取,
                 * 而且一次信号的到来，一定是一个完整的struct signalfd_siginfo数据大小*/
                assert(readed == sizeof(sifd));
                showSignalfd_SignalInfo(&sifd);
            }
        }
    }


    if(epoll_ctl(efd, EPOLL_CTL_DEL, sfd, NULL) < 0) {
        perror("epoll_ctl ");
        close(sfd);
        close(efd);
        return 1;
    }

    close(sfd);
    close(efd);

    if(sigprocmask(SIG_SETMASK, &oldMask, NULL) < 0) {
        perror("sigprocmask ");
        return 1;
    }

    return 0;
}

