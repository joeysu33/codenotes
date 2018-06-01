/*!
 * 获取各种调度策略的调度数值范围
*  输出结果
 * SCHED_RR和SCHED_FIFO都是 [1,99]
 * SCHED_OTHER, SCHED_BATCH, SCHED_IDLE 都是0,可见SCHED_OTHER, SCHED_BATCH, SCHED_IDLE均是通过nice来设置权重
 */

#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


/*!实时策略的priority数值*/
struct {
    char *name;
    int sched;
    int min, max;
} sched[] = {
    {"SCHED_FIFO", SCHED_FIFO, 0, 0},
    {"SCHED_RR", SCHED_RR, 0, 0 },
    {"SCHED_OTHER", SCHED_OTHER, 0, 0},
    {"SCHED_BATCH", SCHED_BATCH, 0, 0},
    {"SCHED_IDLE", SCHED_IDLE, 0, 0},
};

int
main() {
    int i, j, prio;
    int lastErr;

    lastErr = errno;
    for(i=0, j=sizeof(sched)/sizeof(sched[0]); i<j; ++i) {
        /*!因为返回值可以是负值*/
        errno = 0;
        prio = sched_get_priority_min(sched[i].sched);
        if(errno != 0) {
            perror("sched_get_priority_min()");
            return 1;
        }

        sched[i].min = prio;
        prio = sched_get_priority_max(sched[i].sched);
        if(errno != 0) {
            perror("sched_get_priority_max()");
            return 1;
        }
        sched[i].max = prio;
    }
    errno = lastErr;

    for(i=0, j=sizeof(sched)/sizeof(sched[0]); i<j; ++i) {
        printf("%s: min=%d, max=%d.\n", sched[i].name, sched[i].min, sched[i].max);
    }

    return 0;
}

