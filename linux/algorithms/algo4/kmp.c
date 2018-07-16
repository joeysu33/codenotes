#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>

/*!
 * 构建next表,next表的构建
 * next[j+1]
 * 当p[j] == p[t]的时候next[j+1]=next[j]+1
 * 否则next[j] = next[next[j]],直到匹配位置
 * 最后一定会收敛于N[0]=-1,因为N[0]==-1的时候
 * -1可以匹配任何数值，也就是除了N[0]=-1之外，
 *  其他的都>-1
 */

static const char *s1 = "abcdeabcd";

int* 
next(const char *p) {
    int i,j, t, len;
    int *n;

    len = strlen(p);
    n = malloc(len * sizeof(int));

    t = -1;
    j = 0;
    n[j] = t;
    while(j < len-1) {
        if(t < 0 || p[j] == p[t]) {
            t++;
            j++;
            /*!计算n[j+1],通过n[j], p[j] ?= p[t]*/
            if(p[j] != p[t]) {
                n[j] = t;
            } else {
                n[j] = n[t];
            }
        } else {
            t = n[t];
        }
    }

    return n;
}

void
showNext(const char *p) {
    int *n;
    int len, i;
    const char *cp;

    len = strlen(p);
    if(!p) return ;
    for(cp = p; *cp; ++cp) {
        printf("%-4c", *cp);
    }
    printf("\n");

    n = next(p);
    for(i=0; i<len; ++i) {
        printf("%-4d", *(n+i));
    }
    printf("\n\n");

    free(n);
}

int
main(int argc, char *argv[]) {
    showNext(s1);
    return 0;
}

