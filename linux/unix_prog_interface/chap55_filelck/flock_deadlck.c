/*!
 * flock死锁的测试程序，flock的fork子进程会继承锁,
 * fcntl不会继承记录锁
 */

#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[]) {
    return 0;
}

