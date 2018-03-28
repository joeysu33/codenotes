/*!
 * 获取时间
 * gettimeofday 和time都是获取时间，获取的是从纪元(epoch)，
 * 1970年1月1号零点开始经过的秒数(其中gettimeofday还精确包含了微妙)
 * gettimeofday比time更精确，由BSD提供，描述的都是UTC时间
 */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include "../common/common.h"

int main(int argc, char *argv[]) {
    time_t t1;
    struct timeval tv;

    while(1) {
        t1 = time(NULL);
        if(t1 == -1) err_exit("time(NULL)");
        if(gettimeofday(&tv, NULL) == -1) err_exit("gettimeofday(&tv,NULL)");
        assert(tv.tv_sec == t1);
        printf("tv.tv_sec=%ld tv.tv_usec=%ld, t1=%ld\n", tv.tv_sec, tv.tv_usec, t1); 
        sleep(1);
    }
    return 0;
}
