/*!
 * BSD劝告锁的使用
 * fcntl是System-V的记录锁（劝告锁)
 * int flock(int fd, int opt);
 *
 * opt:
 * 1.LOCK_SH 共享锁
 * 2.LOCK_EX 互斥锁
 * 3.LOCK_UN 解锁
 * 4.LOCK_NB 以非阻塞方式操作（获取锁)
 *
 * flock是对整个文件进行锁
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/file.h> //System-V的头文件貌似都在sys目录下

int
main(int argc, char *argv[]) {
    return 0;
}

