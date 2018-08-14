/*!
 * 图算法之最小生成树(Minimum Spanning Tree), MST
 *
 * 在图中每一颗支撑树的成本即其所采用各边的权重的总和。
 * 在G的所有支撑树中，成本最低的称为最小支撑树
 *
 * Prim算法（普利姆算法）：首先从边中选择一条最短边，然后
 * 不断的加入外部顶点(新加入的边作为割边)，直到顶点的个数等于所有顶点的和
 *
 * Kruskal算法（克鲁斯卡尔算法）：初始的时候每个顶点都是一颗树，总是从
 * 边中选择一条最小边，来连接两棵树（改边是割边）。
 *
 * Prim算法是不断增加新的点，让树逐渐长大，最终树的节点树等于顶点数。
 * Kruskal算法是不断的增加新的边，让子树进行合并，最终长成一颗大树，边的条数为N-1
 *
 * Prim算法和Kruskal的算法复杂度都是e*loge,prim算法适合dense tree(边多点少),而
 * kruskal算法适合sparse tree(边少点多)
 */


#include <ctype.h> //isdigit isblank
#include "common.h"

#define NBUFFER 4096
#define NMAX 100

struct _Edge ;

typedef struct _Vertex {
    char m_c;
    //struct _Vertex *m_next; //child of vertex 
    struct _Edge *m_edge;
} Vertex, *PVertex, *Graph;

typedef struct _Edge {
    int m_vertex;
    int m_prio;
    struct _Edge *m_next;
} Edge, *PEdge;

void
readLine(char *buf, int *i) {
    *i = 0;
    char c;
    if(!buf || !i) return ;
    while((c = fgetc(stdin)) != EOF) {
        if(c == '\n') {
            buf[*i]='\0'; //设置空字符
            break;
        }
        buf[(*i)++] = c;
        if(*i == NBUFFER) assert(false);
    }
}

bool
isEmpty(char *buf) {
    if(!buf) return true;
    while(*(buf++)) {
        if(!isblank(*buf)) { return false; }
    }
    return true;
}

bool
isComment(char *buf) {
    if(!buf) return true;
    return (*buf == '#');
}

void
readDataLine(char *buf, int *i) {
    do{
        readLine(buf, i);
    }while(isComment(buf) || isEmpty(buf));
}

Edge*
makeEdge(int vertex, int val) {
    Edge *e = (Edge*)malloc(sizeof(Edge));
    e->m_next = NULL;
    e->m_vertex = vertex;
    e->m_prio = val;
    return e;
}

Graph 
makeGraph(int *vc, int *ec) {
    int m, n, i, j; //顶点个数、边的条数
    char buffer[NBUFFER];
    char sym[255], c, k;
    Edge **e, *e1;

    readDataLine(buffer, &i);
    sscanf(buffer, "%d%d", &m, &n);

    if(m < 1 || n <1) return NULL;

    readDataLine(buffer, &i);
    Graph g = (Graph) malloc(sizeof(Vertex) * m);
    Vertex *v;

    char *p = buffer;
    for(j=0; j<m && (*p); p++) {
        if(isblank(*p)) continue;

        g[j].m_edge = NULL; //bugs-7 索引值j写成i了
        //sscanf(buffer, "%c", &c); //这样读，始终读第一个bugs-1
        c = *p;
        g[j].m_c = c; //这里索引值写错了，j写成i了
        sym[c] = j; //符号表索引值
        j++;
    }

    do {
        readDataLine(buffer, &i);
        if(i == 0 ) break; //read EOF
        //sscanf(buffer, "%c", &c); //始终读第一个bugs-2
        sscanf(buffer, "%c%*[^a-zA-Z0-9]%c%d", &c, &k, &j);
        v = &g[sym[c]];
        //sscanf(buffer, "%c%d", &c, &j); //始终从第一个开始读，bugs-3
        //e = &v->m_edge; //bugs-4，多维指针的乱用
        //while(*e) *e = (*e)->m_next;
        if(!v->m_edge) { 
            e = &v->m_edge; 
        } else {
            e1 = v->m_edge;
            while(e1->m_next) e1 = e1->m_next;
            e = &e1->m_next;
        }
        *e  = makeEdge(sym[k], j);
    } while(1);

    *vc = m; *ec = n;
    return g;
}

void
freeGraph(Graph *g, int vc) {
    int i;
    Edge *e, *pe;
    for(i=0; i<vc; ++i) {
        e = (*g)[i].m_edge;
        while(e) {
            pe = e;
            e = e->m_next;
            free(pe);
        }
        (*g)[i].m_edge = NULL;
    }
    free(*g);
    *g = NULL;
}

/*!
 * 构建一个堆，总是从堆中找到距离最近的顶点*/
void
prim(Graph g, int vc, int ec) {
    int prio[NMAX][NMAX], visited[NMAX], vertex[NMAX];
    int i, j, k,minEdge = INT_MAX, iv=0; //边的条数
    Edge *e;
    int prioSum = 0;

    //设置初始值,-1表示不存在这样的边
    for(i=0; i<NMAX; ++i)
        for(j =0; j<NMAX; ++j)
            prio[i][j] = INT_MAX;

    //初始化v
    for(i=0; i<NMAX; ++i) visited[i] = 0;

    //找出一条最小的边，作为最开始的顶点
    j = -1, k=-1;
    for(i=0; i<vc; ++i) {
        e = g[i].m_edge;
        while(e) {
            prio[e->m_vertex][i] = prio[i][e->m_vertex] = e->m_prio; //无向图
            printf("e[%d][%d]=e[%d][%d]=%d\n", i, e->m_vertex,
                    e->m_vertex, i, e->m_prio);
            if(e->m_prio < minEdge) {
                j = i;
                k = e->m_vertex;
                minEdge = e->m_prio;
            }
            e = e->m_next;
        }
    }

    visited[j] = 1; visited[k] = 1;
    //新增两个顶点
    vertex[iv++] = j; 
    vertex[iv++] = k;
    prioSum += minEdge;

    //bugs-6 将vertex[i]写成了i
    do {
       minEdge = INT_MAX;
       k = -1;
       for(i=0; i<iv; ++i) {
           for(j=0; j<vc; ++j) {
               if(vertex[i] != j && !visited[j] && prio[vertex[i]][j] < minEdge) {
                   k = j;
                   minEdge = prio[vertex[i]][j];
               }
           }
       }

       //如果图是联通的k一定存在
       assert(k >= 0);
       visited[k] = 1;
       vertex[iv++] = k;
       prioSum += minEdge;
    } while(iv < vc);

    for(i=0; i<iv; ++i) {
        //g[vertex[i]].m_c = 'x';
        printf("%c ", g[vertex[i]].m_c);
    }
    printf("\n");
    printf("MST prio:%d\n", prioSum);
}


void
kruskal(Graph g, int vc, int ec) {
}

int
main(int argc, char *argv[]) {
    //要先使用深度优先算法来确定该图是连通的
    int vc, ec;
    Graph g = makeGraph(&vc, &ec);
    prim(g, vc, ec);
    freeGraph(&g, vc);

    return 0;
}






