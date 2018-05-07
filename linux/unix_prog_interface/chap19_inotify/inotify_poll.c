/*!
 * 使用poll来检测inotify文件描述符
 */

#include <sys/inotify.h> //inotify_init, inotify_add_watch, inotify_rm_watch, struct inotify_event
#include <sys/poll.h> //poll
#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdint.h> //uint8_t, uint32_t

#define MAXPOLLFD 10


#define PRINT(...) \
    do { printf(__VA_ARGS__); printf("\n"); }while(0)

#define PMASK(msk) \
    do {if(ev->mask & msk) {printf(#msk); printf(", "); } }while(0)

unsigned dirExists(const char* dirname) {
    struct stat st;
    if(stat(dirname, &st) == -1) {
        return 0;
    }

    return (st.st_mode & S_IFDIR) ;
}

void
showInotifyEvent(struct inotify_event* ev) {
    if(!ev) return ;
    PRINT("wd=%2d", ev->wd);
    PRINT("mask=%d", ev->mask);
    PRINT("cookie=%d", ev->cookie);
    PMASK(IN_ACCESS);
    PMASK(IN_ATTRIB);
    PMASK(IN_CLOSE_NOWRITE);
    PMASK(IN_CLOSE_WRITE);
    PMASK(IN_CREATE);
    PMASK(IN_DELETE);
    PMASK(IN_DELETE_SELF);
    PMASK(IN_IGNORED);
    PMASK(IN_ISDIR);
    PMASK(IN_MODIFY);
    PMASK(IN_MOVE_SELF);
    PMASK(IN_MOVED_FROM);
    PMASK(IN_MOVED_TO);
    PMASK(IN_OPEN);
    PMASK(IN_Q_OVERFLOW);
    PMASK(IN_UNMOUNT);
    if(ev->len > 0) {
        PRINT("name = %s", ev->name);
    }
    PRINT("\n");
}
int 
main(int argc, char* argv[]) {
    /*!almost read 10 (struct inotify_event) */
    char buf[sizeof(struct inotify_event) *2 +1 ];
    struct pollfd pfd[MAXPOLLFD];
    int i, j,n;
    int timeout; //ms
    int ifd, fd;
    uint32_t mask;
    ssize_t readed;
    struct inotify_event *iev;

    if(argc != 2) {
        fprintf(stderr, "%s <dir>\n", argv[0]);
        return 1;
    }

    if(!dirExists(argv[1])) {
        fprintf(stderr, "%s is not exists.\n", argv[1]);
        return 1;
    }

    ifd = inotify_init1(IN_NONBLOCK | IN_CLOEXEC); //和epoll_create, epoll_create1类似
    if(ifd < 0) {
        perror("inotify_init1");
        return 1;
    }

    //mask = IN_ACCESS | IN_ATTRIB | IN_CREATE | IN_DELETE | IN_MODIFY | IN_OPEN;
    mask = IN_ALL_EVENTS;
    fd = inotify_add_watch(ifd, argv[1], mask);
    if(fd < 0) {
        perror("inotify_add_watch");
        return 1;
    }

    for(i=0; i<10; ++i) {
        memset(&pfd[i], 0, sizeof(struct pollfd));
        pfd[i].fd = -1;
    }

    /*!!特别警告!!!, 一个ifd可以读取很多数据*/
    /*!****从ifd读取数据*******/
    pfd[0].fd = ifd;
    pfd[0].events = POLLIN;
    timeout = -1; //wait forever

    for(;;) {
        n=poll(pfd, MAXPOLLFD, timeout);
        if(n < 0) {
            if(errno == EINTR) continue;

            perror("poll");
            return 1;
        } else {
            printf("data come---\n");
            /*!wait forever*/
            for(i=0; i<MAXPOLLFD; ++i) {
                if(pfd[i].fd < 0) continue;
                if(!(pfd[i].revents & POLLIN)) continue;

reread:
                readed = read(pfd[i].fd, buf, sizeof(buf));
                if(readed < 0) {
                    if(errno == EINTR) goto reread;
                    perror("read");
                    return 1;
                } else {
                    for(j=0; j<readed; ) {
                        iev = (struct inotify_event*) ((char*)buf + j);
                        showInotifyEvent(iev);
                        /*!inotify的长度两部分组成*/
                        j += sizeof(struct inotify_event) + iev->len;
                    }
                }

            }
        }
    }

    return 0;
}

