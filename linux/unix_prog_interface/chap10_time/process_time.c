/*!
 * 获取当前进程花费的时间
 * clock_t times(struct tms *buf);
 * struct tms {
 * clock_t tms_utime,  //user cpu time
 * clock_t tms_stime,  //system cpu time
 * clock_t tms_cutime, //user cpu time of all (waited for) children
 * clock_t tms_cstime, //sys cpu tim of all (waited for children)
 */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>    //sysconf
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/times.h> //times
#include "../common/common.h"

void
show_proc_time() {
    long clock_tck ;
    struct tms buf;
    /*! mostly _SC_CLK_TCK = 100 */
    clock_tck = sysconf(_SC_CLK_TCK);
    if(times(&buf) == -1) err_exit("times");
    printf("_SC_CLK_TCK=%ld\n", clock_tck);
    printf("usertime:%.3lf\n\
cputime:%.3lf\n\
childusertime:%.3lf\n\
childcputime:%.3lf \n",buf.tms_utime*1.0/clock_tck,
                                    buf.tms_stime*1.0/clock_tck,
                                    buf.tms_cutime*1.0/clock_tck,
                                    buf.tms_cstime*1.0/clock_tck);

}

unsigned long 
counter() {
    int i;
    unsigned long c;
    c=0;
    for(i=1; i<10000000; ++i) {
        c +=sqrt(1);
    }
    return c;
}

int
main(int argc, char *argv[]) {
    unsigned long i;
    int j;
    pid_t pid = fork();

    for(j=0; j<2; ++j) 
        i = counter();

    if(pid == 0) {
        for(j=0; j<3; ++j) 
            i = counter();
        printf("child pid=%d\n", getpid());
        sleep(2);
        exit(0);
    } else { 
        int st;
        /*! wait == waitpid(-1, &st, 0) */
        if(wait(&st) == -1) {
            err_exit("wait");
        }
        printf("child retcode:%d\n", st);
        show_proc_time();
    }

    return 0;
}

