/*!
 * 更新（设置）系统时钟 (UTC时间）
 * settimeofday -> gettimeofday
 * stime -> time
 */

#define _BSD_SOURCE
#define _XOPEN_SOURCE

#include <sys/time.h> //support settimeofday & gettimeofday
#include <time.h>
#include "../common/common.h"

int main(int argc, char *argv[]) {
    struct tm tm;
    time_t t;
    if(argc < 3) {
        printf("%s strtime timefmt\n", argv[0]);
        return -1;
    }

    if(strptime(argv[1], argv[2], &tm) == NULL) err_exit("strptime:%s,%s", argv[1],argv[2]);
    t = mktime(&tm);
    if(t == -1) err_exit("mktime");
    if(stime(&t) == -1) err_exit("stime");

    return 0;
}

