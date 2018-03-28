/*!
 * c开发中，主要的time操作分类
 * 1.获取UTC时间，从1970年1月1号0点开始计算的秒数，类型time_t
 *   -gettimeofday
 *   -time
 * 2.将UTC时间可以转换成一个日历时间，struct tm { int tm_sec, int tm_min,...}
 *   -gmtime
 *   -localtime
 * 3.将UTC时间转换为字符串的时间
 *   -ctime (相当于time_t t=time(NULL); struct tm *tt = localtime(&t); const char *ts = asctime(tt);
 * 4.将struct tm*转换位时间字符串
 *   -asctime
 *   -strftime (需要参考格式化)
 * 5.将struct tm转换为time_t
 *   -mktime
 * 6.将字符串的日历转换为tm,
 *   -strptime (需要参考格式化)
 */

/*!strptime */
#define _XOPEN_SOURCE

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <memory.h>
#include "../common/common.h"

static struct tm g_tm;
static struct tm g_tm2;

/*!
 * epoch (纪元)
 *获取utc时间
 */
time_t get_utc_time() {
    time_t t;
    struct timeval tv;
    if(gettimeofday(&tv, NULL) == -1) err_exit("gettimeofday");
    t = time(NULL);
    assert(tv.tv_sec == t);
    return t;
}

/*!
 * 根据time_t获取 struct tm
 */
struct tm* get_tm(bool gmtime) {
    time_t t=get_utc_time();
    if(localtime_r(&t, &g_tm) == NULL) err_exit("localtime_r");
    if(gmtime_r(&t, &g_tm2) == NULL) err_exit("gmtime_r");
    if(gmtime) return &g_tm2;
    return &g_tm;
}

/*!
 * utc 转日历字符串
 */
const char *utc_to_str() {
    time_t t = get_utc_time();
    return ctime(&t);
}

/*!
 * struct tm转字符串
 */
void tm_to_str() {
    struct tm *tm1, *tm2;
    tm1 = get_tm(true);
    /*!
     * 特别需要注意asctime返回的是一个静态存储，不能释放
     * 也不能这么调用
     * printf("tm1=%s tm2=%s", asctime(tm1), asctime(tm2));
     * 因为asctime指向的都是同一块内存区域
     */
    printf("tm1=%s\n", asctime(tm1));
    tm2 = get_tm(false);
    printf("tm2=%s\n", asctime(tm2));
}

void tm_format_s(const char* s) {
    char buf[256];
    printf("fmt_string:%s\n",s);
    if(strftime(buf, sizeof(buf),s,  get_tm(true)) == 0) err_exit("strftime:%s", s);
    printf("%s\n", buf);
}

void tm_format_str() {
    tm_format_s("%m");
    tm_format_s("%c");
}

/*!
 * struct tm转utc,mktime
 */
time_t tm_to_utc(struct tm* t) {
    (void)t;
    struct tm *tm = get_tm(true);
    time_t now = time(NULL);
    time_t tnow = mktime(tm);
    assert(tnow == now);
}

/*!
 * str转 struct tm
 */
struct tm* str_to_tm() {
    memset(&g_tm, 0, sizeof(g_tm));
    strptime("2017-11-10 5:36:10", "%Y-%m-%d %H:%M:%S", &g_tm);
    printf("time:%s\n", asctime(&g_tm));
    return &g_tm;
}

int main(int argc, char* argv[]) {
    get_utc_time();
    printf("utc-str:%s\n",utc_to_str());
    tm_to_str();
    tm_format_str();
    str_to_tm();
    return 0;
}

