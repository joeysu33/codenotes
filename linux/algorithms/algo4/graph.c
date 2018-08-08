/*!
 * Breadth First Search 广度优先搜索算法
 * Adjacency v-v
 * Incidence v-e
 *
 * G(v, e)
 * 使用邻接表实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>


#define NQMAX 8

typedef enum _EdgeState{
    ES_UNDEFINED = 0, //未定义
    ES_TREE, //树型延伸
    ES_FORWARD, //发现的节点是当前节点的子孙
    ES_BACKWARD, //发现的节点是当前节点的祖先
    ES_CROSS, //表亲、兄弟关系
} EdgeState;

typedef enum _VertexState {
    VS_UNDISCOVERED = 0, //未发现
    VS_DISCOVERED, //发现
    VS_VISITED, //已经访问
} VertexState;

static char * vstat[] = {
    "Undefined",
    "Tree",
    "Forward",
    "Backward",
    "Cross",
};

static char * estat[] = {
    "Undiscovered",
    "Discovered",
    "Visited",
};

//标记时间, dtime, atime
typedef int Time;
typedef struct _Edge Edge;

//顶点描述
typedef struct _Vertex {
    int m_d;
    VertexState m_st;
    Time m_dtime, m_atime;
    Edge *m_edge;
} Vertex, *PVertex;

//边描述,边中含一个顶点的索引值
//indicence 关联方式实现
typedef struct _Edge {
    EdgeState m_st;
    int m_weight;
    int m_vertex;
    Edge *m_next;
} Edge, *PEdge;

//图
typedef struct _Graph {
    int m_vc, m_ec; 
    Vertex *m_vertex;
    Time m_clock;
} Graph, *PGraph;

typedef struct _EdgeIndex {
    int m_i, m_j;
} EdgeIndex;

void
initVertex(Vertex *v) {
    if(!v) return ;
    v->m_d = 0;
    v->m_st = VS_UNDISCOVERED;
    v->m_dtime = v->m_atime = 0;
    v->m_edge = NULL;
}

void
initEdge(Edge *e) {
    if(!e) return ;
    e->m_st = ES_UNDEFINED;
    e->m_weight = -1;
    e->m_vertex = -1; //索引值
    e->m_next = NULL;
}

Vertex*
newVertex(char c) {
    Vertex *v = (Vertex*)malloc(sizeof(Vertex));
    if(!v) return NULL;
    initVertex(v);
    v->m_d = c;
    return v;
}

Edge*
newEdge(int i) {
    if(i < 0) return NULL;
    Edge *e = (Edge*)malloc(sizeof(Edge));
    if(!e) return NULL;
    initEdge(e);
    e->m_vertex = i;
    return e;
}

void
addVertex(Graph *g, char c) {
    Vertex *v;
    if(!g) return ;
    v = (Vertex*)malloc((g->m_vc+1) * sizeof(Vertex));
    if(!v) return ;
    memcpy(v, g->m_vertex, sizeof(Vertex) * g->m_vc);
    initVertex(&v[g->m_vc]);
    g->m_vc++;

    free(g->m_vertex);
    g->m_vertex = v;
}

void
addEdge(Graph *g, int i, int j) {
    if(!g || i<0 || i>=g->m_vc ||
            j<0 || j>=g->m_vc) {
        return ;
    }
    Edge *e = newEdge(j);
    if(!e) return ;

    Edge **pe = &g->m_vertex[i].m_edge;
    while(*pe) {
        /*!要引用自己，需要再次引用*/
        //ERROR: *pe = (*pe)->m_next;
        pe = &(*pe)->m_next;
    }
    *pe = e;
}

/*!
 * 释放本次edge，返回下一次的edge*/
Edge*
freeEdge(Edge *e) {
    Edge *next = e->m_next;
    free(e);
    return next;
}

void
freeGraph(Graph *g) {
    int i;
    Edge *e;
    for(i=0; i<g->m_vc; ++i) {
        e = g->m_vertex[i].m_edge;
        do {
            e = freeEdge(e); 
        }while(e);
    }

    free(g->m_vertex);
    g->m_vertex = NULL;
    g->m_vc = g->m_ec = 0;
}

Vertex*
getVertex(Graph *g, int i) {
    if(!g || i < 0 || i>=g->m_vc) return NULL;
    return &g->m_vertex[i];
}

void
setVertexCount(Graph *g, int vc) {
    if(!g || vc < 1) return ;
    freeGraph(g);
    g->m_vertex = (Vertex*)malloc(sizeof(Vertex) * vc);
    g->m_vc = vc;
}

void
setVertex(Graph *g, int index, char c) {
    if(!g || index < 0 || index >= g->m_vc) return ;
    g->m_vertex[index].m_d = c;
}

void
findVertex(Graph *g, int i) {
    Vertex * v = getVertex(g, i);
    if(!v) return ;

    printf("Found Vertex:%c, dtime=%d, atime=%d, state=%s\n",
            v->m_d,
            v->m_dtime,
            v->m_atime,
            vstat[v->m_st]);
}

void
findEdge(Graph *g, int i, Edge *e) {
    if(!e) return ;

    Vertex *v1 = getVertex(g, i);
    Vertex *v2 = getVertex(g, e->m_vertex);
    if(!v1 || !v2) assert(0);

    printf("Found Edge(%c->%c): weight=%d\n", v1->m_d, v2->m_d, e->m_weight);
}

/*!
 * 示例 (有向图)
 * s a b c d e f g (8个顶点)
 * s, ->a, ->c, ->d,
 * a, ->c, ->e,
 * b, NULL
 * c, ->b
 * d, ->b,
 * e, ->f, ->g
 * f, ->NULL
 * g, ->b, ->f
 * 合计11条边
 * s:0
 * a:1
 * b:2
 * c:3
 * d:4
 * e:5
 * f:6
 * g:7
 */
void
makeGraph(Graph *g) {
    char vetexs[] = {'s', 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
    EdgeIndex edges[] = { {0, 1}, {0,3}, {0, 4},
                            {1, 3}, {1,5},
                            {3, 2},
                            {4, 2},
                            {5, 6}, {5,7},
                            {7, 2}, {7,6}};

    int vc = sizeof(vetexs)/sizeof(vetexs[0]);
    int ec = sizeof(edges)/sizeof(edges[0]);
    int i;
    setVertexCount(g, vc);
    for(i=0; i<vc; ++i) setVertex(g, i, vetexs[i]);
    for(i=0; i<ec; ++i) addEdge(g, edges[i].m_i, edges[i].m_j);
}


void
initGraph(Graph *g) {
    if(!g) return ;
    g->m_vc = g->m_ec = 0;
    g->m_clock = 0;
    g->m_vertex = NULL;
}

int
qIsEmpty(int front, int rear) ;
int
qIsFull(int front, int rear) ;

void
enqueue(int *q, int *front, int *rear, int d) {
    if(!q) return ;
    if(qIsFull(*front, *rear)) assert(0);
    q[(*rear++) % NQMAX] = d;
}

int
dequeue(int *q, int *front, int *rear) {
    if(!q) return -INT_MAX;
    if(qIsEmpty(*front, *rear)) assert(0);
    int r = q[(*front++) % NQMAX];
    return r;
}

int
qIsEmpty(int front, int rear) {
    return front == rear ? 1 : 0;
}

int
qIsFull(int front, int rear) {
    return ((rear+1) % NQMAX) == front ? 1 : 0;
}

void
bfs_sub(Graph *g, int i) {
    if(!g || i < 0 || i >= g->m_vc) return ;

    //构建一个循环队列,默认认为图中一行数据（一排子节点）的个数不大于100
    int q[NQMAX], qf = 0, qr = 0;
    int m, n;
    Vertex *v, *v1;
    Edge *e;
    enqueue(q, &qf, &qr, i);

    while(!qIsEmpty(qf, qr)) {
        m = dequeue(q, &qf, &qr);
        if(m < 0 || m >= g->m_vc) assert(0);
        v = &g->m_vertex[m];
        e = v->m_edge;
        v->m_st = VS_DISCOVERED;
        v->m_dtime = ++g->m_clock;

        //获取与m相关联的所有vertex，并入队列
        while(e) {
            v1 = getVertex(g, e->m_vertex);
            assert(v1);

            switch(v1->m_st) {
                case VS_UNDISCOVERED:{
                                        enqueue(q, &qf, &qr, e->m_vertex);
                                        e->m_st = ES_TREE;
                                        findEdge(g, m, e);
                                        break;
                                     }
                default: e->m_st = ES_CROSS; break;
            }

            e = e->m_next;
        }

        //完成该顶点的下一步工作（找邻接之后完成任务)
        v->m_st = VS_VISITED;
        v->m_atime = ++g->m_clock;
        findVertex(g, e->m_vertex);
    }
}

/*!
 * 广度优先算法*/
void
bfs(Graph *g) {
    if(!g) return ;
    int i;
    Vertex *v;

    for(i=0 ; i<g->m_vc; ++i) {
        v = getVertex(g, i);
        if(!v) assert(0);
        if(v == VS_UNDISCOVERED)
            bfs_sub(g, i);
    }
}

/*!
 * 深度优先算法*/
void
dfs(Graph *g) {
    if(!g) return ;
}

int
main(int argc, char *argv[]) {
    Graph g;
    initGraph(&g); 
    makeGraph(&g);
    bfs(&g);
    freeGraph(&g);

    return 0;
}




