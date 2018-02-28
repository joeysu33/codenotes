#include "common.h"

#include <assert.h>
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

void set_graph_value(int i, int j, byte value);

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




