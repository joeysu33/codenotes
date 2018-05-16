/*!
 * 进程的退出码
 * 1.正常退出，进程的最大退出码255,如果retcode > 255,则返回码是 retcode= retcode%256
 * 2.信号退出，是128+n, n是信号的编号，例如使用SIGINT退出，则退出码是130,SIGQUIT是131
 *
 * 进程退出码的建议是不要大于128,大于128可以认为是信号退出的处理，一定不能大于255
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int retcode = 0;
    if(argc > 1) {
        retcode = atoi(argv[1]);
        printf("input retcode=%d\n", retcode);
    } else {
        /*!使用信号退出*/
        printf("start to sleep 5 sec...\n");
        sleep(5);
    }

    return retcode;
}

