/*!
 * 文件记录锁的测试
 * int fcntl(int fd, int cmd, ...);
 */ 

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#define TESTFILE "testfile"

void
showLock(struct flock *flk) {
    printf("l_type=%d,"
            "l_whence=%d,"
            "l_start=%ld,"
            "l_len=%ld\n",
            flk->l_type,
            flk->l_whence,
            flk->l_start,
            flk->l_len);
}

int
main(int argc, char *argv[]) {
    struct flock flk, flk2;
    int fd, cmd;
    fd = open(TESTFILE, O_WRONLY | O_CREAT, 0660);
    if(fd < 0) {
        perror("open");
        return 1;
    }
    if((ftruncate(fd, 512)) < 0) {
        close(fd);
        perror("ftruncate");
        return 1;
    }

    flk.l_type = F_WRLCK;
    flk.l_whence = SEEK_SET;
    flk.l_start = 80;
    flk.l_len = 20;

    cmd = F_SETLK;
    if(fcntl(fd, cmd, &flk) < 0) {
        close(fd);
        perror("fcntl");
        return 1;
    }

    cmd = F_GETLK;
    memset(&flk2, 0, sizeof(struct flock));
    /*!这里只能获取锁的类型，其他的信息获取不到，
     * 得在其他进程中操作*/
    if(fcntl(fd, cmd, &flk2) < 0) {
        perror("fcntl-flk2");
        close(fd);
        return 1;
    }

    showLock(&flk2);
    close(fd);
    return 0;
}

