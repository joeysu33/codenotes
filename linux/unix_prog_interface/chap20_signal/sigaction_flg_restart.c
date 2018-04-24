/*!
 * sigaction 
 * SA_RESTART标志位
 * 用来表示在进行系统调用或库调用过程中，如果发生中断信号，执行
 * 中断处理之后继续执行调用,
 * 否则调用失败（一般返回-1)，并返回EINTR
 */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h> //support strsignal
#include <strings.h> //support strcasecmp忽略大小写比较, 相应的strncasecmp,strcmp, strncmp

void
action_handler(int sig) {
    printf("Caught signal-(%d): %s\n", sig, strsignal(sig));
}

int
main(int argc, char*argv[]) {
    char buf[16];
    struct sigaction sa;
    int nReaded;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = action_handler;
    
    /*!
     * error: when result != 0 
     */
    if(setvbuf(stdout, NULL, _IONBF, 0) ) {
        perror("setvbuf ");
    }

    if(argc >= 2 && !strcasecmp(argv[1], "restart")) {
        sa.sa_flags |= SA_RESTART;
        printf("sa_flags != SA_RESTART\n");
    }

    if(sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction ");
        return 1;
    }

    while(1) {
        //nReaded = read(STDOUT_FILENO, buf, sizeof(buf)-1);
        //if(nReaded == -1) {
        if(!fgets(buf, sizeof(buf), stdin)) {
            perror("fgets ");
        } else {
            //buf[nReaded]=0;
            printf("s=%s\n", buf);
        }
    }

    return 0;
}

