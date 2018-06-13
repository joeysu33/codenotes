/*!
 * 管道（未命名管道)
 *
 * #include <unistd.h>
 * int pipe(int pipefd[2]);
 * int pipe2(int pipeffd[2], int flags);
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <limits.h> //PIPE_BUF
#include <sys/types.h>
#include <sys/wait.h>

#define handle_error(s) \
    do { perror(s); exit(EXIT_FAILURE); }while(0)

int
main() {
    int s, i, rn;
    int pfd[2];

    /*!只要一次写入的数据小于或等于PIPE_BUF,
     * 则写入操作是原子的，（假如存在多个写入
     * 的话，不会将写入混淆写入)
     */
    char buf[PIPE_BUF/2];
    struct {
        int len;
        char buf[64];
    } pd;
    assert(sizeof(pd.buf) < PIPE_BUF);
    
    printf("PIPE_BUF=%d.\n", PIPE_BUF);
    s = pipe(pfd);
    if(s < 0) {
        handle_error("pipe");
    }

    s = fork();
    if(s < 0) {
        handle_error("fork");
    } else if (s == 0) {
        close(pfd[0]);
        for(i=0; i<5; ++i) {
            snprintf(buf, sizeof(buf), "testabc:%d", i); 
            /*!写入定长的字符作为边界*/
            write(pfd[1], buf, sizeof(buf));
        }
        close(pfd[1]); //close的时候会写入0
        _exit(0);
    }

    close(pfd[1]);
    i=0;
    for(;;) {
        /*!读取定长的字符作为边界*/
        rn = read(pfd[0], buf, sizeof(buf));
        if(rn == 0) {
            printf("read EOF,when i=%d\n", i);
            close(pfd[0]);
            break;
        } else if(rn < 0) {
            handle_error("read");
        } else {
            /*!对字节流数据要自己筛选*/
            printf("read:%d bytes, loop-%d:%s\n", rn, ++i, buf);
        }
    }

    waitpid(-1, &s, 0);
    return 0;
}

