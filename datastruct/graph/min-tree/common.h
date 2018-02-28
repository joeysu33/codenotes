#if !defined(_MINTREE_COMMON_INCLUEDED_H)
#define _MINTREE_COMMON_INCLUEDED_H

#include <stdio.h>

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

void init_graph();
int graph_edge_count();
Edge* graph_edges();
byte get_value_from_graph(int i, int j);

void print_graph(Edge *edge, int n);

typedef struct _Edge {
    int i,j;
    byte value;
} Edge;

typedef struct _Graph {
    int vertex[N];
    Edge edges[N*N/2];
} Graph;

#endif //_MINTREE_COMMON_INCLUEDED_H

