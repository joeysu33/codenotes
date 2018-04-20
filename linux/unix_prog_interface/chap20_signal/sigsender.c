/*!
 * 发送大量信号到指定的进程
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int
main(int argc, char*argv[]) {
    int tPID, sig, nums, lastSig;
    int i;
    if(argc != 5) {
        printf("%s <pid> <sig_nums> <sig> <last_sig>\n", argv[0]);
        return 1;
    }

    tPID = atoi(argv[1]);
    if(tPID <= 0) return 2;
    nums = atoi(argv[2]);
    if(nums < 1) return 2;
    sig = atoi(argv[3]);
    if(sig < 1 || sig > 31) return 2;
    lastSig = atoi(argv[4]);
    if(lastSig < 1 || lastSig > 31) return 2;

    for(i=0; i<nums; ++i) {
        if(kill(tPID, sig) < 0) {
            perror("kill ");
            return 3;
        }
    }
    printf("Send to pid=%d, sig=%d %d times.\n", tPID, sig, nums);

    if(kill(tPID, lastSig) < 0) {
        perror("kill ");
        return 4;
    }
    printf("Send to pid=%d, sig=%d\n", tPID, lastSig);

    return 0;
}


