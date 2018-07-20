/*!
 * Boyee Moore算法
 * 由两个并行算法构成
 * bc (Bad Character)算法，取匹配的最右侧值，画家算法
 * gs (Good Suffxi) 算法，从字符串中找到和后缀相同的进行匹配
 *   -ss (Suffix Size)，计算匹配后缀的长度算法O(m^2)，也可以优化到O(m)
 *   -完成ss之后，需要进行如下两种情况的处理,需要注意的是：先完成(1)的操作，然后进行(2)的操作
 *    (1)j+1 == ss[j],也就是从索引0开始的和后缀相匹配，例如aaaxxxxaaa, 或者ajofewjaaa，
 *       令m为strlen(P), 令i < m-j-1, 则所有的gs[i] = m-j-1,默认滑到最前面
 *    (2)j+1 != ss[j], gs[m-ss[j]-1] = m-j-1;
 *
 * 主程序框架:从最后一个字符串开始匹配，一旦不匹配，则从bc和gs中取最大的偏移量，
 *            虽然bc的返回值有可能是负数（产生回溯,因为返回的值是最右侧的索引 j-bc['Right Most Character']），但是gs的值一定是正数（>=1)
 * **该算法需要达到的程度，可进行口算
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
_max(int a, int b) { return a > b ? a : b; }
int
_min(int a, int b) { return a < b ? a : b; }

#define NSYM 256 //ASCII, 如果是Unicode的话，应该是两个字符2^16

//Bad Character
int*
makeBC(const char *p) {
    int i, j,k;
    int *bc;
    if(!p) return NULL;
    k = strlen(p);
    bc = (int*)malloc(k * sizeof(int));

    /*!画家算法，向右移动，如果右侧有相同的字符会进行覆盖*/
    for(i=0; i<k; ++i) {
        bc[p[i]] = i;
    }

    return bc;
}

//Suffix Size
int*
makeSS(const char *p) {
    int i, j, k, m;
    int *ss;

    if(!p) return NULL;
    k = strlen(p);
    ss = (int*)malloc(k * sizeof(int));

    /*!从右向左，从倒数第二个字符开始，依次和末尾的字符串进行比较*/
    ss[k-1] = k;
    for(i=k-2; i>=0; --i) {
        j = i;
        for(; j >= 0 && p[j] == p[k-1-(i-j)]; --j) {}

        /*!在位置i处，写入从i开始(包含i), 向左移动和后缀匹配的长度 */
        ss[i] = i-j;
    }

    return ss;
}

//Good Suffix
int*
makeGS(const char *p) {
    int i, j, k ;
    int *ss, *gs;
    
    if(!p) return NULL;
    k = strlen(p);
    ss = makeSS(p);
    gs = (int*)malloc(sizeof(int) * k);

    /*!gs表进行初始化*/
    for(i=0; i< k; ++i) gs[i] = k;

    /*!处理的时候分为两种情况，匹配位置在最左侧*/
    //case1,满足条件 ss[j] == j+1, gs[i] = m-j-1,当且仅当i< m-1-j时
    //因为case1，一旦前缀和后缀匹配，就会将数值都设置为m-j-1,所以处理的顺序必须是
    //从右至左，因为越往左侧，匹配后缀的长度越短，那么移动的长度越长...,移动长度是m-j-1,j减小时
    //m-j-i增大
    for(i=k-1; i>=0; --i) {
        if(i+1 == ss[i]) {
            //将小于m-j-1的位置，全部置为m-j-1
            for(j=0; j < k-i-1; ++j) {
                gs[j] = k-i-1;
            }
        }
    }
    
    /*!处理的时候分为两种情况，匹配位置在中间位置*/
    //case2,满足条件 gs[m-1-ss[j]] = m-j-1
    for(i=0; i<k; ++i) {
        gs[k-1-ss[i]] = k-1-i;
    }

    return gs;
}

int
bm (const char *t, const char *p) {
    int *bc, *gs;
    int i, j, k, tlen, plen;
    char umatched ;

    if(!t || !p) return -1;

    bc = makeBC(p);
    gs = makeGS(p);
    tlen = strlen(t);
    plen = strlen(p);
    for(i=0, j = tlen - plen; i <= j;) {
        /*! P从右至左来查找,一旦不匹配，使用bc和gs来定位下一个位置*/
        for(k= plen-1; k>=0; --k) {
            if(t[i+k] != p[k]) {
                break;
            }
        }

        /*!已经找到*/
        if(k < 0) {
            free(bc); free(gs);
            return i; 
        }

        /*!定位下一个不匹配的位置*/
        umatched = t[i+k]; /*!找到Text中不匹配的char*/
        i += _max(gs[k], k-bc[umatched]);
    }

    free(bc); free(gs);
    return -1;
}

#define FIND(t, p) \
    do {\
        const char *pt = #t, *pp = #p;\
        int i= bm(pt, pp);\
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





