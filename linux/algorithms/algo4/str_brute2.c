/*!
 * 串-暴力搜索算法2
 * 使用两层for循环
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
    int i, j, ok;
    int m = strlen(t), n = strlen(p);
    for(i=0; i<m; ++i) {
        ok = 1;
        for(j=0; j<n; ++j) {
            if(p[j] != t[i+j]) ok = 0;
        }

        if(ok) return i;
    }

    return -1;
}

int
main(int argc, char *argv[]) {
    int i;
    i = match(ss, ps);
    printf("%s, i=%d\n", i<0 ? "not match" : "match", i);
    return 0;
}

