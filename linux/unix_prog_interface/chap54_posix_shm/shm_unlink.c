/*
 * shm_unlink 删除posix内核共享对象
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

int
main(int argc, char *argv[]) {
    if(argc != 2) {
        return 1;
    }

    if(shm_unlink(argv[1]) < 0) {
        perror("shm_unlink");
        return 1;
    }

    printf("delete %s posix_shm success!\n", argv[1]);
    return 0;
}
