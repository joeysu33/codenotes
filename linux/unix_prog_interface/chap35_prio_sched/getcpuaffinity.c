/*!
 *
 * #define _GNU_SOURCE
 * #include <sched.h>
 *
 * 获取CPU的默认亲和度
 * int sched_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask);
 * int sched_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *mask);
 *
 * cpusetsize = sizeof(cpu_set_t)
 * 返回-1表示错误
 *
 * int sched_getcpu(); 获取当前CPU的编号，从0开始
 *
  */

#define _GNU_SOURCE //sched_XXX

#include <sched.h> //sched_XXXX
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> //kill

int
main(int argc, char *argv[]) {
    int i, pid, s, j;
    char *endptr;
    cpu_set_t mask;
    long cmask, cpucnt;

    CPU_ZERO(&mask);
    cpucnt = sysconf(_SC_NPROCESSORS_CONF);
    if(argc < 2) {
        fprintf(stderr, "%s: <pid> <pid> ....\n", argv[0]);
        return 1;
    }

    for(i=0; i<argc; ++i) {
        if(i) {
            pid = strtol(argv[i], &endptr, 0);
            /*!发送0信号进行测试，判断该进程是否是有效进程*/
            if(kill(pid, 0) < 0) {
                printf("pid=%d is not a valid process.\n", pid);
                continue;
            }
        } else {
            pid = 0; /*!自身*/
        }

        printf("sizeof(cpu_set_t)=%ld.\n", sizeof(cpu_set_t));
        s = sched_getaffinity(pid, sizeof(cpu_set_t), &mask);
        if(s < 0) {
            perror("sched_getaffinity()");
            return 1;
        }

        for(cmask=0,j=0; j<cpucnt; ++j) {
            cmask |= 0x1 << j;
        }
        printf("pid=%d cpu-mask:0x%lx\n", pid?pid:getpid(), cmask);
    }

    return 0;
}


