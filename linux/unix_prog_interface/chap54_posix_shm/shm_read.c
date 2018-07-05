#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>


int
main(int argc, char *argv[]) {
    int fd;
    long len;
    char *buf;
    void *addr;

    if(argc != 3) {
        return 1;
    }

    len = strtol(argv[2], &buf, 0);
    if(len <= 0) {
        return 1;
    }

    if((fd = shm_open(argv[1], O_RDONLY, 0)) < 0) {
        perror("shm_open");
        return 1;
    }

    buf = malloc(len);
    addr = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    memcpy(buf, addr, len);
    printf("read success:%s, size=%ld\n", buf, len);
    free(buf);
    munmap(addr, len);

    return 0;
} 
