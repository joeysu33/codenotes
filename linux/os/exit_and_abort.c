/*!
 * 测试exit和abort和kill,通过信号触发的退出，没有刷新stdio缓存区
 * 而exit和abort刷新了
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

static char iobuffer[512];

int
main(int argc, char *argv[]) {
    int i;
    char abortmode;
    if(argc != 2) {
        printf("%s <abort | exit>", argv[0]);
        fflush(stdout);
        return 1;
    }

    abortmode = 0;
    if(strcmp(argv[1], "abort") == 0) {
        abortmode = 1;
    } else if(strcmp(argv[1], "kill") == 0) {
        abortmode = 2;
    } 

    if(setvbuf(stdout, iobuffer, _IOFBF, sizeof(iobuffer)) != 0) {
        perror("setvbuf ");
        return 1;
    }

    for(i=1; i; --i)
        printf("测试输出, ");

    printf("------");
    if(abortmode == 1) {
        abort();
    } else if(abortmode == 2) {
        kill(getpid(), SIGINT);
    } else {
        exit(0);
    }

    return 0;
}

