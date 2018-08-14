#include <stdio.h>
#include <memory.h>
#include <string.h>
//#include <malloc.h>

/*!
 * 构建next表,next表的构建
 * next[j+1]
 * 当p[j] == p[t]的时候next[j+1]=next[j]+1
 * 否则next[j] = next[next[j]],直到匹配位置
 * 最后一定会收敛于N[0]=-1,因为N[0]==-1的时候
 * -1可以匹配任何数值，也就是除了N[0]=-1之外，
 *  其他的都>-1
 *
 *  kmp算法，可以增加bc来进行优化
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
kmp(const char *t, const char *p) {
    int i, j, k, tlen, plen;
    int *nxt;

    tlen = strlen(t), plen = strlen(p);
    k = tlen - plen;
    nxt = next(p);

    for(i=0, j=0; i < tlen && j < plen ;) {
        if(j < 0 || t[i] == p[j]) {
            ++j;
            ++i;
        } else {
            j = nxt[j];
            //bf算法
            //i -= j-1;
            //j = 0;
        }
    }

    free(nxt);
    if(j == plen) return i-j;
    return -1;
}

#define FIND(t, p) \
    do {\
        const char *pt = #t, *pp = #p;\
        int i= kmp(pt, pp);\
        if(i<0) {\
            printf("Not found for %s\n", pp);\
        } else {\
            printf("Found it for %s, position = %d\n", pp, i) ;\
        }\
    }while(0)

int 
main(int argc, char *argv[]) {
    FIND(aifjeiwjfoaajofjoewfjoafdsfjsfsf, jeiwj);
    FIND(jeiwjaifjfoaajofjoewfjoafdsfjsfsf, jeiwj);
    FIND(1903240jeiwjaifjfoaajofjoewfjoafdsfjsfsjeiwjf, jeiwj);
    FIND(1903240eiwjaifjfoaajofjoewfjoafdsfjsfsjeiwjf, jeiwj);
    FIND(ccccc, jeiwj);

    return 0;
}

/*
int
main(int argc, char *argv[]) {
    showNext(s1);
    return 0;
}
*/
