/*!
 * 使用特权优先级来解决常见图问题
 * 1.图的广度搜索
 * 2.图的深度搜索
 * 3.图的拓扑排序 (深度搜索的引申)
 * 4.MST
 *  4.1 Prim算法
 *  4.2 Kruskal算法
 */

#include "common.h"

#define NMAX 100
#define UNDIAGRAM 

//g表示图，数据表示图的权值
//vs表示顶点的状态 0:未发现 1:发现 2:已经访问
//vp表示顶点之间建立的节点关系（可以找到某个索引的父节点) -1:表示没有父亲节点
//vprio表示顶点的特权值，用来更细特权值，并选取下一个顶点, 特权值越小，特权越高
static int g[NMAX][NMAX] , vs[NMAX], vp[NMAX], vprio[NMAX];
static int m, n;

/*!
 * 优先权的更新函数,根据某种贪心策略来确定下一个取出的元素 */
typedef void (PRIFUNC) (int u, int v) ;

/*!
 * Deepth First Search */
void
priDFS(int u, int v) {
}

/*!
 * Breadth First Search */
void
priBFS(int u, int v) {
}

void
priTopnology(int u, int v) {
}

void
priPrimAlgo(int u, int v) {
}

void
priKruskalAlgo(int u, int v) {
}

int nextNbr(int i, int j) {
    if(i < 0 || i >= m ||
            j < 0 || j >= m) return -1;
    while(--j >= 0 && g[i][j] == 0) ;
    return j;
}

int firstNbr(int i) {
    return nextNbr(i, m-1);
}

void
PFS(int i, PRIFUNC prif) {
    vs[i] = 1;  //discovered
    vp[i] = -1;
    vprio[i] = 0; //最高特权

    //将下一个顶点和边加入到PFS中
    int j, k;
    while(true) {
        for(j = firstNbr(i); j > 0; j = nextNbr(i, j)) 
            prif(i, j); //更新权值表
        for(j = INT_MAX, k=0; k<m; ++k) {
            //新的顶点
            if(!vs[k]) {
                if(j > vprio[k]) {
                    j = vprio[k];
                    i = k;
                }
            }
        }

    }
}

/*!
 * 优先权的算法 */
void
pfs(PRIFUNC func) {
    int i , k;
    //for(i=0; i<m; ++i) vp[i] = -1;  //重置父节点状态信息
    memset(vs, 0, sizeof(vs));//重置vs的状态

    i=0; k = i;
    do {
        if(!vs[i]) 
            PFS(i, func);
        i++;
    } while( (i+1)%m != k); //可以从任何位置开始图（所以图在某些时候不具备唯一性)
}

int
main(int argc, char* argv[]) {
    int pair[2], i, j, k; //vs:顶点状态 0:未发现 1:发现 2:访问
    char c, str[16], *cp;
    printf("Enter numbers of vertexes and edges:");
    fflush(stdout);
    scanf("%d%d", &m, &n);

    memset(g, 0, sizeof(g));
    memset(vs, 0, sizeof(vs));
    memset(vp, 0, sizeof(vp));

    if(m < 1 || n < 1 || m >= NMAX || n > NMAX*NMAX) return 1;
    int st=-1; //st== -2注释行
    while((c = fgetc(stdin)) != EOF) {
        switch(c) {
            case '(':{
                         if(st == -2) break;
                         assert(st == -1);
                         st++;
                         i=0;j = -1;
                         break;
                     }
            case ',': {
                          if(st == -2) break;
                          assert(st == 0 || st == 1);
                          str[i]=0;
                          if(st == 0) {
                              pair[0] = strtol(str, &cp, 0);
                          } else {
                              pair[1] = strtol(str, &cp, 0);
                          }
                          i=0;
                          st++;
                          break;
                      }
            case ')': {
                          if(st == -2) break;
                          assert(st == 2);
                          str[i]=0;
                          k = strtol(str, &cp, 0);
                          g[pair[0]][pair[1]] =  k;
#if defined(UNDIAGRAM)
                          g[pair[1]][pair[0]] =  k;
#endif
                          st = -1;
                          break;
                      }
            case '#': {
                          st = -2; break;
                      }
            case '\n': {
                           if(st == -2) st = -1; 
                           break;
                       }
            default: {
                         if(st == -2) break;
                         if(st == 0 || st == 1 || st == 2)
                             str[i++] = c;
                         break;
                     }
        }
    }

    pfs(priDFS);
    return 0;
}




