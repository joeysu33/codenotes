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
    int * ip, i, j, x, M, c, size;

    int ** res = (int **)malloc(sizeof(int*) * NSYM);
    M = strlen(p);
    size = sizeof(int) * M;
    for(i=0; i<NSYM; ++i) {
        res[i]  = (int *)malloc(size);
        //***********对所有的数据进行初始化（非常重要)
        memset(res[i], 0, size);
    }

    /*!构造DFA表*/
    x=0, j=1;
    res[p[x]][x] = j; /*! 输入第一个字符进入状态1 */
    for(; j < M; j++) {
        //计算dfa[][j]
        for(c =0; c < NSYM; c++) {
            res[c][j] = res[c][x];
        }
        res[p[j]][j]  = j+1; /*! 状态更新 */
        x = res[p[j]][x];    /*! 设置新的上一次状态 */
    }

    return res;
}

void
showTab(int symb, int *tab, int m) {
    int i;
    printf("[%c] \n",symb);
    for(i=0; i<m; ++i) printf("%4d ", tab[i]); printf("\n");
}

void
showKmp(const char *p) {
    int i, j, k, sym[NSYM];
    int **dfa;
    k = strlen(p);
    dfa = makeDFA(p);
    for(i=0; i<NSYM; ++i) {
        sym[i] = 0;
    }
    for(i=0; i<k; ++i) {
        sym[p[i]] += 1;
    }

    for(i=0; i<NSYM; ++i) {
        if(sym[i] > 0) {
            showTab(i, dfa[i], k);
        }
    }

    for(i=0;i< NSYM; ++i) {
        free(dfa[i]);
    }
    free(dfa);
    printf("\n");
}

int
kmp(const char *t, const char *p) {
    int i, j, m, n, k;
    int ** dfa;
    if(!t || !p) return -1;
    m = strlen(t), n = strlen(p);

    dfa = makeDFA(p);
    //showKmp(p);
    /*!j表示当前的状态，默认初始状态是0 */

    //*******这里如果写成 i <= k，如果查找字符串在尾部，则根本找不到????
    //k = m-n
    //这里不能写成 i<=k,因为这里i就是索引自己，而不是t[i+j]，如果是t[i+j]那么可以这么写

    for(i=0,j=0; i<m && j<n ; ++i) {
        j = dfa[t[i]][j]; //i必须取m,因为这里i描述的是不断的输入流
        if(j == n) {
            break;
        }
    }

    //================================================================
    //标准的算法4，写法，会让i多加一次
    //for(i=0; j=0; i < m && j < n; ++i)
    //  j = dfa[t[i]][j]; //如果一旦j == n,i已经多加了一次
    //if(j == n) return i-j ; //因为i已经多加了一次，这里就可以直接i-j

    for(k=0; k<NSYM; ++k) 
        free(dfa[k]);
    free(dfa);
    if(j == n) return i-j+1; /*!这里特别需要注意，因为j表示的是长度，所以需要+1,相当于i-(j-1) */
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
    //showKmp("ababac");
    //showKmp("aifjeiwjfoaajof");
    //return 0;


    FIND(aifjeiwjfoaajofjoewfjoafdsfjsfsf, jeiwj);
    FIND(jeiwjaifjfoaajofjoewfjoafdsfjsfsf, jeiwj);
    FIND(1903240jeiwjaifjfoaajofjoewfjoafdsfjsfsjeiwjf, jeiwj);
    FIND(1903240eiwjaifjfoaajofjoewfjoafdsfjsfsjeiwjf, jeiwjf);
    FIND(1903240eiwjaioafdsfjsfsjeiwjjeiwjjeiwjf, jeiwj);
    FIND(ccccc, jeiwj);

    return 0;
}

