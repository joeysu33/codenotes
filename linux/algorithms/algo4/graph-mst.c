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
            buf[*i]=0;
            break;
        }
        buf[(*i)++] = c;
        if(*i == NBUFFER) assert(false);
    }
}

bool
isEmpty(char *buf) {
    if(!buf) return false;
    while(*(buf++)) {
        if(!isblank(*buf)) { return true; }
    }
    return false;
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
    }while(!isComment(buf) && !isEmpty(buf));
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
    char sym[255], c;
    Edge **e;

    readDataLine(buffer, &i);
    sscanf(buffer, "%d%d", &m, &n);

    if(m < 1 || n <1) return NULL;

    readDataLine(buffer, &i);
    Graph g = (Graph) malloc(sizeof(Vertex) * m);
    Vertex *v;

    for(j=0; j<m; ++j) {
        g[i].m_edge = NULL;
        //g[i].m_next = NULL;
        sscanf(buffer, "%c", &c);
        g[i].m_c = c;
        sym[c] = j; //符号表索引值
    }

    do {
        readDataLine(buffer, &i);
        sscanf(buffer, "%c", &c);
        v = &g[sym[c]];
        sscanf(buffer, "%c%d", &c, &j);
        e = &v->m_edge;
        while(*e) *e = (*e)->m_next;
        *e  = makeEdge(sym[c], j);
    } while(i > 0);

    *vc = m; *ec = n;
    return g;
}

void
freeGraph(Graph g, int vc) {
    int i;
    Edge *e, *pe;
    for(i=0; i<vc; ++i) {
        e = g[i].m_edge;
        while(e) {
            pe = e;
            e = e->m_next;
            free(pe);
        }
        g[i].m_edge = NULL;
    }
    free(g);
}

/*!
 * 构建一个堆，总是从堆中找到距离最近的顶点*/
void
prim(Graph g, int vc, int ec) {
    int a[NMAX],b[NMAX], prio[NMAX], v[NMAX]; //新建的顶点(a,b)索引集合, 权值集合,顶点的集合
    Edge *e;
    int i, j, k,minEdge = INT_MAX, ie = 0 ,iv=0; //边的条数

    //找出一条最小的边，作为最开始的顶点
    j = -1, k=-1;
    for(i=0; i<vc; ++i) {
        e = g[i].m_edge;
        while(e) {
            if(e->m_prio < minEdge) {
                j = i;
                k = e->m_vertex;
            }
            e = e->m_next;
        }
    }

    a[ie] = j; b[ie] = k;
    prio[ie++] = minEdge;
    v[iv++] = j; v[iv++] = k;

    for(i=0; i<vc; ++i) {
        minEdge = INT_MAX;
        for(j=0; j<iv; ++j) {
            if(v[j] == i) continue;

            for(k=0; k<ie; ++k) {
                if((a[k] == i && b[k] == j) ||
                    (a[k] == j && b[k] == i)) continue;

                //找到新的边,并找到最小边
            }
        }
    }
}


void
kruskal(Graph g, int vc, int ec) {
}

int
main(int argc, char *argv[]) {
    return 0;
}






