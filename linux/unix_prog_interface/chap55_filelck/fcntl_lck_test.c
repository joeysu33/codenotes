/*!
 * 文件记录锁的测试
 * int fcntl(int fd, int cmd, ...);
 * fcntl（记录锁是不能锁住自己的）
 * 但是flock通过dup文件描述符是可以自己锁住自己的
 */ 

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>

#define TESTFILE "testfile"

void
showLock(struct flock *flk) {
    char *ty;
    switch(flk->l_type) {
        case F_RDLCK: ty = "RDLCK"; break;
        case F_WRLCK: ty = "WRLCK"; break;
        case F_UNLCK: ty = "UNLCK"; break;
        default: ty = "Unknown";
    }
    printf("l_type=%s,"
            "l_whence=%d,"
            "l_start=%ld,"
            "l_len=%ld\n",
            ty,
            flk->l_whence,
            flk->l_start,
            flk->l_len);
}

void
showLock2(int fd, struct flock *flk) {
    struct flock flk2;
    memset(&flk2, 0, sizeof(struct flock));
    /*!这里只能获取锁的类型，其他的信息获取不到，
     * 得在其他进程中操作*/
    if(fcntl(fd, F_GETLK, &flk2) < 0) {
        perror("fcntl-flk2");
        return;
    }

    showLock(&flk2);
}

int
main(int argc, char *argv[]) {
    struct flock flk, flk2;
    int fd, cmd, sleepcnt;
    char *cp;

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

    sleepcnt = 3;
    if(argc > 1) {
        sleepcnt = strtol(argv[1], &cp, 0);
        sleepcnt = sleepcnt < 0 ? 5 : sleepcnt;
    }
    showLock2(fd, &flk);

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

    sleep(sleepcnt);

    showLock2(fd, &flk);

    close(fd);
    return 0;
}

