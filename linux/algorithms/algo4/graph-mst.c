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
 * Prim算法是不断增加新的点，让树逐渐长大，最终树的节点数等于顶点数。
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

void
addEdge(Graph g, int i, int j, int prio) {
    Vertex *v =  &g[i];
    Edge *e = v->m_edge, **pe;
    if(!e) pe = &v->m_edge;
    else { 
        while(e->m_next) e = e->m_next;
        pe = &e->m_next;
    }
    *pe =  makeEdge(j, prio);
}

void
addBiEdge(Graph g, int i, int j, int prio) {
    addEdge(g, i, j, prio);
    addEdge(g, j, i, prio);
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
        //v = &g[sym[c]];
        //sscanf(buffer, "%c%d", &c, &j); //始终从第一个开始读，bugs-3
        //e = &v->m_edge; //bugs-4，多维指针的乱用
        //while(*e) *e = (*e)->m_next;
        /*if(!v->m_edge) { 
            e = &v->m_edge; 
        } else {
            e1 = v->m_edge;
            while(e1->m_next) e1 = e1->m_next;
            e = &e1->m_next;
        }
        *e  = makeEdge(sym[k], j);
        */
        addBiEdge(g,sym[c], sym[k], j);

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
    int prio[NMAX][NMAX], visited[NMAX], vertex[NMAX]; //存储边，存储已经处理完成的顶点和该顶点的索引值
    int i, j, k,minEdge = INT_MAX, iv=0; //边的条数
    Edge *e;
    int prioSum = 0;

    //设置初始值,-1表示不存在这样的边
    for(i=0; i<NMAX; ++i)
        for(j =0; j<NMAX; ++j)
            prio[i][j] = INT_MAX;

    //初始化v
    for(i=0; i<NMAX; ++i) visited[i] = 0;

    for(i=0; i<vc; ++i) {
        e = g[i].m_edge;
        while(e) {
            prio[i][e->m_vertex] = e->m_prio; //无向图
            printf("e[%d][%d]=%d\n", i, e->m_vertex, e->m_prio);
            e = e->m_next;
        }
    }
    
    //找出一条最小的边，作为最开始的顶点
    /*j = -1, k=-1;
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
    */

    //任意选定一个顶点开始
    k = rand() % vc; //给定任意值
    printf("from %c start!!!\n", g[k].m_c);
    visited[k] = 1;
    vertex[iv++] = k;

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
dfsSub(Graph g, int index, int *visited) {
    if(index < 0) return ;
    *(visited+index) = true;
    Vertex *v = &g[index];
    Edge *e = v->m_edge;
    while(e) {
        if(!visited[e->m_vertex]) {
            dfsSub(g, e->m_vertex, visited);
        } 
            
        e = e->m_next;
    }
}

/*!
 * 是否是无向连通图*/
bool
isConnected(Graph g, int vc) {
    int visited[NMAX], i, j;
    for(i=0; i<vc; ++i) visited[i]=false;
    for(i=0, j=0; i<vc; ++i) {
        if(!visited[i]) {
            dfsSub(g, i, visited);
            j++;

            if(j > 1) return false;
        }
    }
    return true;
}

/*!
 * UF (Union/Find)操作 */
int
ufFind(int *arr, int x) {
    if(!arr || x < 0) return INT_MAX;
    if(arr[x] < 0) return x;
    return arr[x] = ufFind(arr, arr[x]); //含路径压缩find
}

void
ufUnion(int *arr,int x, int y) {
    if(!arr || x < 0 || y < 0) return ;
    int xr = ufFind(arr, x), yr = ufFind(arr, y);
    if(xr == yr) return ;

    //对x和y的树(从根部)进行合并
    arr[yr] = xr;
}

void
ufInit(int *arr, int size) {
    int i;
    for(i=0; i<size; ++i) arr[i] = -1;
}

int
ufNumsOfConnected(int *arr, int size) {
    int i, n;
    for(i=0, n=0; i<size; ++i) {
        if(arr[i] < 0) n++;
    }
    return n;
}

void
kruskal(Graph g, int vc, int ec) {
    //将边存储到数组中
    typedef struct _EdgeData { int m_inda, m_indb, m_prio, m_visited; } EdgeData;
    EdgeData ed[NMAX], tmp, *ptmp;
    int i , j, k, a, edge, uf[NMAX], prioSum;
    Vertex *v;
    Edge *e;

    ufInit(uf, vc);
    //堆的构建从1开始，0作为哨兵, 1~N
    for(i=0, j=0; i<vc; ++i) {
        v = &g[i];
        e = v->m_edge;
        while(e) {
            ++j;
            k = e->m_vertex;
            ed[j].m_inda = i;
            ed[j].m_indb = k;
            ed[j].m_prio = e->m_prio;
            ed[j].m_visited = 0;
            e = e->m_next;
        }
    }

    //assert(j*2 == ec && j > 1);
    //构建大根堆,自下而上进行下滤percolateDown
    //最后一个根节点j-1,最后一个根节点1
    for(i = j/2; i>0; --i) {
        //percolateDown下滤操作
        tmp = ed[i];
        a = i;
        while(true) {
            k = 2 * a;
            if(2*a+1 <= j && ed[2*a +1].m_prio > ed[k].m_prio) {
                k = 2*a + 1;
            }
            if(k <= j && tmp.m_prio < ed[k].m_prio) {
                ed[a] = ed[k];
                a = k;
            } else  break;
        }
        ed[a] = tmp;
    }

    //堆排序（省事一点)
    for(i=j;i > 1; ) { //最后一个值可以忽略1
        //和最后一个位置进行对调
        tmp = ed[1];
        ed[1] = ed[i];
        ed[i] = tmp;

        //下滤操作，堆的规模缩短至i--
        i--;
        tmp = ed[1];
        a = 1;
        while(true) {
            k = 2 * a;
            if(2*a +1 <=i && ed[2*a+1].m_prio > ed[k].m_prio) k = 2*a+1;
            if(k <= i && ed[k].m_prio > tmp.m_prio) { //bugs-10 特别注意，如果使用移动数据则都是用值，不再使用索引
                ed[a] = ed[k];
                a = k;
            } else break;
        }
        ed[a] = tmp;
    }

    edge = 0;
    k = 1; //从1开始
    prioSum = 0; 
    a = j;
    do {
        //从已经堆排序的数据中取出最小的
        assert(k <= a && k > 0);
        ptmp = &ed[k];
        if(ptmp->m_visited) {
            k++; continue;
        }

        i = ufFind(uf, ptmp->m_inda);
        j = ufFind(uf, ptmp->m_indb);

        if(i == j) {
            k++;
            continue; //i和j必须分属不同的连通图
        }
        printf("(%c, %c, %d) ",ptmp->m_inda + 'a', ptmp->m_indb + 'a', ptmp->m_prio);
        ufUnion(uf, i, j);
        ptmp->m_visited = 1;
        edge++; k=1; //从头开始取最小的
        prioSum += ptmp->m_prio;
        printf("{conncted:%d} ", ufNumsOfConnected(uf, vc));
        fflush(stdout);
    } while(edge != vc-1); //edge != ec-1 ? bugs-N要注意判断条件，否则直接死循环
    printf("sum=%d\n", prioSum);
}

void
printLn(const char *title) {
    printf("-----------------%s-----------------\n", title);
}

int
main(int argc, char *argv[]) {
    //要先使用深度优先算法来确定该图是连通的
    int vc, ec;
    srand(time(NULL));
    Graph g = makeGraph(&vc, &ec);
    if(!isConnected(g, vc)) {
        freeGraph(&g, vc);
        return 1;
    }

    printLn("Prim");
    prim(g, vc, ec);

    printLn("Kruskal");
    kruskal(g, vc, ec);
    freeGraph(&g, vc);

    return 0;
}




