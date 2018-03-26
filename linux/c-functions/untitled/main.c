#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int flag=0;
    int fd, n;
    char *p;
    char *np;
    if(strstr(argv[2], "r")) {
        flag = O_RDONLY;
        printf("file readonly.\n");
    } else if(strstr(argv[2], "w")) {
        flag = O_WRONLY;
        printf("file writeonly.\n");
        flag |= O_CREAT;
    } else {
        printf("Invalid input argument.\n");
        return 100;
    }

    fd = open(argv[1],flag, 0664);
    if(fd== -1) {
        printf("open\n");
        return 1;
    }

    if(flag & O_RDONLY) {
        printf("aa");
        p=strstr(argv[2], "r");
        printf("%s", p);
        n = strtol(p+1,&np, 0);
        printf("n=%d\n",n);
        if(n==0 || (p+1) == np) {
            printf("strtol\n");
            return 2;
        }
        p= (char*)malloc(n+1);
        p[n]=0;
        n=read(fd,p, n);
        if(n < 0) {
            free(p);
            printf("read\n");
            return 3;
        }
        printf("read:%s\n", p);
        free(p);
    } else {
        p= strstr(argv[2], "w");
        n=write(fd, p, strlen(p));
        if(n < 0) {
            free(p);
            printf("write\n");
            return 4;
        }
        printf("write:%s\n", p);
    }
    close(fd);

    return 0;
}

