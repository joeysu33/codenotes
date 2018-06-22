/*!
 * 查看当前msq的状态
 * -i id
 * -k k
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <time.h>

void 
showTime(const char* s, const time_t *t) {
    struct tm *ltm;
    char buf[1024];
    ltm = localtime(t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    printf("%s:%s\n", s, buf);
}

void
showPerm(struct ipc_perm *p) {
    /*!unsigned short mode;
     * unsigned short seq; 
     * 8进制来表示
     */
    printf("key=%d, uid=%d, gid=%d,"
            "cuid=%d, cgid=%d,"
            "mode=0%ho,"
            "seq=%hi\n",
            p->__key,
            p->uid, p->gid,
            p->cuid, p->cgid,
            p->mode, p->__seq);
}

void
showMSQ(int id) {
    int n;
    struct msqid_ds msq;
    n = msgctl(id, IPC_STAT, &msq);
    if(n < 0) {
        perror("msgctl");
        exit(1);
    }

    showPerm(&msq.msg_perm);
    showTime("msg_stime", &msq.msg_stime);
    showTime("msg_rtime", &msq.msg_rtime);
    showTime("msg_ctime", &msq.msg_ctime);
    printf("Number of bytes in queue:%lu\n"
            "Number of messages in queeue:%lu\n"
            "Maxinum bytes in queue:%lu\n"
            "PID of last msgsnd:%d\n"
            "PID of last msgrcv:%d\n",
            msq.__msg_cbytes,
            msq.msg_qnum,
            msq.msg_qbytes,
            msq.msg_lspid,
            msq.msg_lrpid);
    fflush(stdout);
}

int
main(int argc, char *argv[]) {
    int i, id, flg;
    key_t k;
    char *ar, *cp;
    
    flg = 0;
    for(i=1; i<argc; ++i) {
        ar = argv[i];
        if(*ar != '-') continue;
        switch(*(++ar)) {
            case 'i': {
                          ++i; 
                          if(i>=argc) return 1;
                          id = strtol(argv[i], &cp, 0);
                          flg = 0x1;
                          break;
                      }
            case 'k': {
                          ++i;
                          if(i>=argc) return 1;
                          flg = 0x2;
                          k = strtol(argv[i], &cp, 0);
                          break;
                      }
        }

        if(flg) break;
    }

    if(!flg) return 1;

    if(flg == 0x2) {
        id = msgget(k, 0);
        if(id < 0) {
            perror("msgget()");
            return 1;
        }
    }

    showMSQ(id);

    return 0;
}
