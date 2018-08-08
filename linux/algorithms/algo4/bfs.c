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

typedef enum _EdgeState{
    ES_UNDEFINED, //未定义
    ES_TREE, //树型延伸
    ES_FORWARD, //发现的节点是当前节点的子孙
    ES_BACKWARD, //发现的节点是当前节点的祖先
    ES_CROSS, //表亲、兄弟关系
} EdgeState;

typedef enum _VertexState {
    VS_UNDISCOVERED, //未发现
    VS_DISCOVERED, //发现
    VS_VISITED, //已经访问
} VertexState;

//标记时间, dtime, atime
typedef int Time;

//无向图的定点描述
typedef struct _Vertex {
    int m_d;
    VertexState m_st;
    Time m_dtime, m_atime;
} Vertex, *PVertex;

//有向图定点描述
typedef struct _DiagraphVertex {
    int m_d;
    VertexState m_st;
    Time m_dtime, m_atime;
    int m_inDegree, m_outDegree;
    struct _DiagraphVertex *m_next;
} DiagraphVertex, *PDiagraphVertex;

//边描述
typedef struct _Edge {
    EdgeState m_st;
    int m_weight;
} Edge, *PEdge;

//无向图
typedef struct _Graph {
    int m_vc, m_ec; 
} Graph, *PGraph;

int
main(int argc, char *argv[]) {
    return 0;
}

