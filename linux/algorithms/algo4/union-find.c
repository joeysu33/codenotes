/*!
 * 等价关系Equivalence Relation (ER)
 * 并查集(Union/Find) Set (主要用于等价关系)
 * 参考数据结构与算法分析-不相交集
 * 主要接口:
 * void union(int x, int y);
 * int find(int x);
 *
 * 1.判断一个点是否属于一个集合(无向图)
 * 2.判断一系列点构成几个连通图(无向图)
 */

#include "common.h"

#define NMAX 100
#define COMPRESS_PATH 
static int s[NMAX]; //对应元素的映射关系

int doFind(int x);
void
doUnion(int x, int y) {
    if(x < 0 || y <0) return ;
    if(doFind(x) == doFind(y)) return ;
    //s[y] = x; 这么编写，仅将x加入到了s[y]中，这里需要做集合合并
    s[doFind(y)] = doFind(x);
}

/*!
 * 判断某个点是否和其他人连通*/
int
doFind(int x) {
    if(s[x] < 0) return x;

#if defined(COMPRESS_PATH)
    return s[x] = doFind(s[x]); //s[x] = doFind(s[x]);做路径压缩
#else
    return doFind(s[x]); //不做路径压缩
#endif
}

/*!
 * 判断当前图的连通数目*/
int
numOfConnected(int size) {
    int n, i;
    for(i=0, n=0; i<size; ++i) {
        if(s[i] < 0) ++n;
    }
    return n;
}

int 
main(int argc, char *argv[]) {
    int i, j, m, st, tuple[2];
    char c, *cp;
    char buffer[16];

    for(i=0; i<NMAX; ++i) s[i] = -1; //-1作为集合标识
    printf("Nums of elements:");
    fflush(stdout);
    scanf("%d", &m);
    if(m < 1) return 1;

    st = -1; //-1:初始状态 st:0:输入左括号 1:输入逗号 处理数据并再次进入-1
    j = 0;
    //输入的等价关系是(索引A, 索引B)
    while((c = fgetc(stdin)) != EOF) {
        switch(c) {
            case '(': { 
                          if(st != -1) return 1;
                          st++;
                          break;
                      }
            case ',': {
                          if(st !=  0) return 1;
                          st++;
                          buffer[j++] = 0; //组合成字符串
                          tuple[0] = strtol(buffer, &cp, 0);
                          j=0;
                          break;
                      }
            case ')': {
                          if(st != 1) return 1;
                          st = -1;
                          buffer[j++] = 0; //组合成字符串
                          tuple[1] = strtol(buffer, &cp, 0);
                          j=0;
                          printf("(%d, %d) ",tuple[0], tuple[1]);
                          doUnion(tuple[0], tuple[1]);
                          break;
                      }
            default: {
                         if(isdigit(c) && (st == 0 || st== 1)) {
                             buffer[j++] = c;
                         } else {
                             printf("ignore:\'%c\'\n", c);
                         }
                     }
        }
    }

    printf("Nums of Connected:%d\n", numOfConnected(m));
    for(i=0; i<m; ++i) {
        printf("%d belong to equivalence relation %d, directed :%d\n", i, doFind(i), s[i]);
    }

    return 0;
}

