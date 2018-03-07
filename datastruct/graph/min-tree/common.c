#include "common.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>

/*
 * A:0 B:1 C:2 D:3 E:4 F:5
 * A-B 6
 * A-C 1
 * A-D 5
 * B-C 5
 * B-E 3
 * C-D 5
 * C-E 6
 * C-F 4
 * D-F 2
 * E-F 6
 */
void init_graph();
int graph_edge_count();
Edge* graph_edges();
byte get_value_from_graph(int i, int j);
void set_graph_value(int i, int j, byte value);
void print_graph(Edge *edge, int n);

#define NUM (N*N/2)
static byte graph[NUM] = {0};
static Edge edges[] = { {0,1,6}, {0,2,1}, {0,3,5},  //A
                           {1,2,5}, {1,4,3},           //B
                           {2,3,5}, {2,4,6}, {2,5,4},  //C
                           {3,5,2},                    //D
                           {4,5,6}                     //E
        };

void set_graph_value(int i, int j, byte value) {
    int t;
    if(i>N || j>N || i<0 || j<0) {
        assert(false);
        return;
    }

    if(i>j) {
        t=i;i=j;j=t;
    }

    t=i*N+j;
    graph[t] = value;
}

void init_graph() {
    int n=sizeof(edges)/sizeof(Edge), i;
    for(i=0; i<n;++i) {
        set_graph_value(edges[i].i, edges[i].j,edges[i].value);
    }
}

byte get_value_from_graph(int i, int j) {
    int t;
    if(i>N || j>N || i<0 || j<0) {
        assert(false);
        return -1;
    }

    if(i>j) {
        t=i;i=j;j=t;
    }

    t=i*N+j;
    return graph[t];
}

void print_graph(Edge *edge, int n) {
    int i;
    if(!edge || n<1) return ;
    for(i=0; i<n; ++i) {
        fprintf(stdout,"%c--%c:%d\n",edge[i].i+'A',edge[i].j+'A', edge[i].value);
    }
    fprintf(stdout,"\n");
}

int graph_edge_count() { return sizeof(edges)/sizeof(Edge); }
Edge* graph_edges() {
    return &edges[0];
}

//-----------------------------------------------------------------------------
void g_init_graph(Graph *graph){
    if(!graph) return ;
    graph->m_vertex=NULL;
    graph->m_vertex_num=0;
    graph->m_edges=NULL;
    graph->m_edges_num=0;
}

void g_add_vertex(Graph *graph, int vertex) {
    int i;
    int *vn;
    if(vertex < 0 || vertex >=N) return;
    if(!graph) return;
    if(g_contains_vertex(graph, vertex) != -1) return ;
    i=g_vertex_num(graph);
    vn = malloc(sizeof(int) * (i+1));
    if(i>0) {
        memcpy(vn,graph->m_vertex, sizeof(int)*i);
    }
    vn[i]=vertex;
    if(i>0)
        free(graph->m_vertex);
    graph->m_vertex=vn;
    graph->m_vertex_num=i+1;
}

void g_delete_vertex(Graph *graph, int vertex) {
    int i,j,k,index;
    int *v;
    if(!graph) return;
    if(vertex<0 || vertex>=N) return;
    i=g_vertex_num(graph);
    index=g_contains_vertex(graph, vertex);
    if(index == -1) return ;

    if(i>1) {
        v=malloc(sizeof(int) * (i-1));
        for(k=0,j=0; k<i; ++k) {
            if(index==k) {
                continue;
            }
            v[j++]=graph->m_vertex[k];
        }
    } else {
        v=NULL;
    }
    free(graph->m_vertex);
    graph->m_vertex=v;
    graph->m_vertex_num=i-1;
}

void g_add_edge(Graph* graph, Edge* edge) {
    int i;
    Edge *ne;
    if(!graph || !edge)  return;
    if(g_contains_edge(graph, edge) != -1) return;
    i=g_edge_num(graph);
    ne=malloc(sizeof(Edge) * (i+1));
    if(i>0)
        memcpy(ne, graph->m_edges,sizeof(Edge)*i);
    ne[i]=*edge;
    if(i>0) free(graph->m_edges);
    graph->m_edges=ne;
    graph->m_edges_num=i+1;
    //printf("edge->i=%d, edge->j=%d\n",edge->i,edge->j);
    g_add_vertex(graph, edge->i);
    g_add_vertex(graph, edge->j);
}

void g_delege_edge2(Graph* graph, Edge edge) {
    Edge* e=g_find_edge(graph, &edge);
    if(e) {
        g_delete_edge(graph,e);
    }
}

bool g_edge_contains_vertex(Graph* graph, int vertex) {
    int i;
    if(!graph) return false;
    for(i=0; i<graph->m_edges_num; ++i) {
        if(graph->m_edges[i].i == vertex) return true;
        if(graph->m_edges[i].j == vertex) return true;
    }
    return false;
}

void g_delete_edge(Graph* graph, Edge*edge) {
    int i,j,k,index;
    Edge *ne;
    if(!graph || !edge)return;
    index=g_contains_edge(graph, edge);
    i=g_edge_num(graph);
    if(index==-1) return ;
    if(i>1) {
        ne=malloc(sizeof(Edge) * (i-1));
        for(k=0,j=0; j<i; ++j) {
            if(index==j) continue;
            ne[k++]=graph->m_edges[j];
        }
    } else {
        ne=NULL;
    }
    free(graph->m_edges);
    graph->m_edges=ne;
    graph->m_edges_num=i-1;

    /*!如果边的顶点不存在则删除该顶点*/
    if(!g_edge_contains_vertex(graph, edge->i)) {
        g_delete_vertex(graph, edge->i);
    }
    if(!g_edge_contains_vertex(graph, edge->j)) {
        g_delete_vertex(graph, edge->j);
    }
}

void g_delete(Graph *graph) {
    if(!graph) return ;
    if(g_vertex_num(graph) > 0) {
        free(graph->m_vertex);
        graph->m_vertex_num=0;
    }
    if(g_edge_num(graph) > 0) {
        free(graph->m_edges);
        graph->m_edges_num=0;
    }
}

int g_vertex_num(Graph *graph) {
    if(!graph) return 0;
    return graph->m_vertex_num;
}

int g_edge_num(Graph* graph) {
    if(!graph) return 0;
    return graph->m_edges_num;
}

int g_contains_vertex(Graph* graph,int vertex) {
    int i, count=g_vertex_num(graph);
    if(!graph) return -1;
    if(vertex<0 || vertex>=N) return -1;
    for(i=0; i<count;++i) {
        if(graph->m_vertex[i]==vertex) return i;
    }
    return -1;
}

int g_contains_edge(Graph* graph, Edge* edge) {
    int i,count=g_edge_num(graph);
    if(!graph || !edge) return -1;
    for(i=0; i<count; ++i) {
        if(&graph->m_edges[i] == edge) {
            return i;
        }
    }

    return -1;
}
Edge* g_find_edge(Graph* graph,Edge* edge){
    if(!graph || !edge) return NULL;
    int i,count;
    Edge* e;
    count=g_edge_num(graph);
    if(g_contains_edge(graph,edge) != -1) return edge;
    for(i=0; i<count;++i) {
        e=&graph->m_edges[i];
        if(e->i==edge->i &&
                e->j==edge->j &&
                e->value==edge->value) {
            return e;
        }
    }
    return NULL;
}

void g_init_graph_data(Graph *graph) {
    int i=0,n;
    if(!graph) return;
    graph->m_vertex = malloc(sizeof(int) * N);
    graph->m_vertex_num = N;
    for(i=0; i<N; ++i) {
        graph->m_vertex[i]=i;
    }
    n = sizeof(edges)/sizeof(Edge);
    graph->m_edges_num = n;
    graph->m_edges = malloc(sizeof(Edge) * n);
    for(i=0; i<n; ++i) {
        graph->m_edges[i]=edges[i];
    }
}

void g_print_graph(Graph *graph) {
    char buffer[128]="vertex:",buf[12];
    int count=g_vertex_num(graph);
    int i;
    if(!graph) return ;
    for(i=0; i<count; ++i) {
        if(i == count-1) {
            sprintf(buf,"%d.", graph->m_vertex[i]);
        } else {
            sprintf(buf,"%d,", graph->m_vertex[i]);
        }
        strcat(buffer, buf);
    }
    printf("%s\n", buffer);

    print_graph(graph->m_edges, graph->m_edges_num);
}

bool g_contains_edge_vertex(Graph* graph, Edge* edge) {
    if(!graph || !edge) return false;
    if(g_contains_vertex(graph, edge->i) != -1) return true;
    if(g_contains_vertex(graph, edge->j) != -1) return true;
    return false;
}





