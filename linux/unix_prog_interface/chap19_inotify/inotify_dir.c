/*!
 * inotify框架
 *
 * 初始化
 * inotify_init();
 * inotify_init1(int flags);
 *
 * 增加监测对象，返回观察对象描述符wd
 * inotify_add_watch(int fd, const char* pathname, int mask);
 *
 * 删除监测对象
 * inotify_rm_watch(int fd, int wd);
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <limits.h> //NAME_MAX 255

#include <sys/inotify.h>
#include <sys/stat.h>
#include <sys/types.h>

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
    int ifd;
    int wd;
    ssize_t numRead;
    struct inotify_event *evt;
    char *p;
    /*!分配buffer的时候，尽量是分配整数个大小的空间，
     * 为了避免空间不足,NAME取NAME_MAX+1
     * (32+255+1) *10
     */
    char buf[10 * (sizeof(struct inotify_event) + NAME_MAX + 1)];

    if(argc != 2) {
        PRINT("%s <dirname>", argv[0]);
        return 1;
    }

    if(!dirExists(argv[1])) {
        return 3;
    }

    ifd = inotify_init();
    if(ifd == -1) {
        perror("inotify_init() ");
        return 2;
    }

    wd = inotify_add_watch(ifd, argv[1], IN_ALL_EVENTS);
    if(wd == -1) {
        perror("inotify_add_watch ");
        return 4;
    }

    PRINT("Start to watching:%s, wd=%2d", argv[1], wd);
    /*!
     * 从inotify文件描述符中读取事件变化，
     * 也可以直接使用select, poll, epoll
     * 来监测事件变化
     */
    while(1) {
        //阻塞模式
        numRead = read(ifd, buf, sizeof(buf));
        if(numRead < 0) {
            perror("read ");
            return 5;
        } else if(numRead == 0) {
            perror("read == 0 ");
            return 6;
        } else {
            for(p = buf; p <buf+numRead;) {
                /*!一次最多接收10个 */
                showInotifyEvent((struct inotify_event*)p);
                /*!inotify_event的长度由两部分构成inotify_event + inotify_event->len */
                p += (sizeof(struct inotify_event) + ((struct inotify_event*)p)->len);
            }
        }
    }

    return 0;
}


