/*!
 * 使用状态机来处理字符串匹配(Regex也是采用这种方法)
 * DFA Deterministic Finite Automation
 * NFA Not Deterministic Finite Automation
 *
 * 例如ababac,构建的状态机，表格
 *      0 1 2 3 4 5  (索引表示状态)
 *      a b a b a c
 * (输入):
 * a    1 1 3 1 5 1 
 * b    0 2 0 4 0 4 
 * c    0 0 0 0 0 6 <结束状态>
 *
 * 状态机DFA的五个要素 <K, M, f, S, Z>
 * K:状态集合
 * M:输入源集合
 * f:转换（函数）
 * S:开始状态
 * Z:结束状态
 *
 * DFA可以用图来描述，也可以用表格来描述
 * 该算法的核心在与如何构建一个状态机，并将状态机的开始
 * 作为0，结束作为模式的长度.
 *
 * 匹配到状态机，则成为模式识别
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSYM 256

/*!构造DFA的表格会比较大 */
int**
makeDFA(const char *p) {
    int * ip, i, j, x, M, c;

    int ** res = (int **)malloc(sizeof(int*) * NSYM);
    M = strlen(p);
    for(i=0; i<NSYM; ++i) {
        res[i]  = (int *)malloc(sizeof(int) * M);
    }

    /*!构造DFA表*/
    res[p[0]][0] = 1; /*! 输入第一个字符进入状态1 */
    for(x = 0, j=1; j < M; j++) {
        //计算dfa[][j]
        for(c =0; c < NSYM; c++) {
            res[c][j] = res[c][x];
        }
        res[p[j]][j]  = j+1;
        x = res[p[j]][x];
    }

    return res;
}

int
kmp(const char *t, const char *p) {
    int i, j, m, n, k;
    int ** dfa;
    if(!t || !p) return -1;
    m = strlen(t), n = strlen(p);

    dfa = makeDFA(p);
    /*!j表示当前的状态，默认初始状态是0 */
    for(i=0, k = m-n, j=0; i <= k; ++i) {
        j = dfa[t[i]][j];
        if(j == m) {
            return i-j;
        }
    }

    for(i=0; i<NSYM; ++i) 
        free(dfa[i]);
    free(dfa);

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

