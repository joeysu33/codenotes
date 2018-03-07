#if !defined(_MINTREE_COMMON_INCLUEDED_H)
#define _MINTREE_COMMON_INCLUEDED_H

#include <stdio.h>

#if !defined(NULL)
#define NULL 0
#endif

#define N 6
#if !defined(byte)
#define byte unsigned char
#endif

#if !defined(true)
#define true 1
#endif

#if !defined(false)
#define false 0
#endif

#if !defined(bool)
typedef byte bool;
#endif

typedef struct _Edge Edge;

typedef struct _Edge {
    int i,j;
    byte value;
} Edge;

typedef struct _Graph {
    int *m_vertex;
    int m_vertex_num;
    Edge *m_edges;
    int m_edges_num;
} Graph;

void g_init_graph(Graph *graph);
void g_print_graph(Graph *graph);
void g_init_graph_data(Graph *graph);
void g_add_vertex(Graph *graph, int vertex);
void g_delete_vertex(Graph *graph, int vertex);
void g_add_edge(Graph* graph, Edge* edge);
void g_delete_edge(Graph* graph, Edge*edge);
void g_delege_edge2(Graph* graph, Edge edge);
void g_delete(Graph *graph);
int g_vertex_num(Graph *graph);
int g_edge_num(Graph* graph);
int g_contains_vertex(Graph* graph,int vertex);
int g_contains_edge(Graph* graph, Edge* edge);
Edge* g_find_edge(Graph* graph,Edge* edge);
bool g_contains_edge_vertex(Graph* graph, Edge* edge);
bool g_edge_contains_vertex(Graph* graph, int vertex);

#endif //_MINTREE_COMMON_INCLUEDED_H

