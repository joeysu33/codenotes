/*!
 * 克鲁斯卡尔算法
 * 此算法可以称为“加边法”，初始最小生成树边数为0，
 * 每迭代一次就选择一条满足条件的最小代价边，加入到最小生成树的边集合里。
 * 1.把图中的所有边按照代价从小达到排序；
 * 2.把图中的n个顶点看成独立的n棵树组成的森林；
 * 3.按照权值从小到大选择边，所选的边连接的两个顶点Ui,Uj应属于两棵不同的树，
 *   则称为最小生成树的一边，并将这两棵树合并为一棵树；
 * 4.重复(3)，直到所有的顶点都在一棵树内或者有n-1条边为止。
 *
 * 使用稀疏矩阵来描述无向图
 */

#include "common.h"

static Graph s_graph;
static Graph* s_gph = &s_graph;

void qsort(Edge* first, Edge* end) {
    if(!first || !end) return ;
    if(first == end) return ;

    Edge* i=first, *j=end-1, *k=first; 
    const int v=k->value, iv=k->i, ij=k->j;
    byte t;

    while(i<j) {
        for(; i<k;++i) {
            if(i->value > v) {
                k->value=i->value;
                k->i=i->i;
                k->j=i->j;
                k = i;
                break;
            }
        }

        for(; k<j;--j) {
            if(j->value < v) {
                k->value = j->value;
                k->i=j->i;
                k->j=j->j;
                k = j;
                break;
            }
        }
    }

    k->value = v;
    k->i = iv;
    k->j = ij;

    /*! k is value's right position*/
    /*需要注意sort函数是否包含end，如果不包含，在写的时候要注意*/
    if(k > first) qsort(first, k);
    if(end > k) qsort(k+1, end);
}

void kruskal_mintree() {
    int n,i;
    bool flag=false;
    Graph result;
    g_init_graph(s_gph);
    g_init_graph_data(s_gph);
    n = g_edge_num(s_gph);

    g_init_graph(&result);
    Edge* edges = s_graph.m_edges;
    qsort(edges, edges+n);
    /*!将简单最短的边加入进去*/
    for(i=0; i<n; ++i) {
        if(!g_contains_edge_vertex(&result, &edges[i])) {
            g_add_edge(&result, &edges[i]);
        }
    }
    //可以直接使用递归的方法来进行计算
    /*!将已经加入的边，连接起来*/
    //while(g_edge_num(&result) != N-1) {
        
    //}
    g_print_graph(&result);
}


int main() {
    kruskal_mintree();
    return 0;
}



