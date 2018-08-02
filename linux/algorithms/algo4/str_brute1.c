/*!
 * 串-暴力搜索算法1
 * 不匹配之后回溯到起始位置
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static const char *ss = "01001000010100100101010100010100010000011";
static const char *ps = "1010008";

/*!
 * 返回-1，搜索失败，否则搜索成功
 */
int match(const char *t, const char *p) {
    int i, j;
    int m = strlen(t), n = strlen(p);
    i=0; j=0;
    while(i < m && j < n) {
        if(t[i] == p[j]) {
            i++;
            j++;
        } else {
            i = (i-j+1);
            j=0;
        }
    }

    if(j==n) return i-j;
    return -1;
}

int
main(int argc, char *argv[]) {
    int i;
    i = match(ss, ps);
    printf("%s, i=%d\n", i<0 ? "not match" : "match", i);
    return 0;
}
