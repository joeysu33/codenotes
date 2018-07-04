/*!
 * 伸展树
 * 1.Top-Down的实现方案
 * 2.Down-Top的实现方案（可能需要额外的存储来保存parent)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMS 10

typedef struct _Node {
    int m_val;
    struct _Node *m_l, *m_r;
} Node, *PNode, *SplayTree;

void
random_data(int *d, const int cnt) {
    int i, j, k, t;
    int sum;
    if(!d) return ;
    for(i=0,sum=cnt*3 ; i<sum; ++i) {
        j = rand() % cnt;
        k = rand() % cnt;

        if(j == k) continue;
        t = d[j];
        d[j] = d[k];
        d[k] = t;
    }
}

void
showTree(SplayTree t)   {
    if(!t) return ;
    showTree(t->m_l);
    printf("%d ", t->m_val);
    showTree(t->m_r);
}

SplayTree L(SplayTree t);
SplayTree R(SplayTree t);

SplayTree
LL(SplayTree t) {
    t->m_l = L(t->m_l);
    return L(t);
}

SplayTree
LL_tarjain(SplayTree t) {
    PNode b, c, d;
    SplayTree p, v;
    p = t->m_l;
    if(!p) return t;
    v = p->m_l;
    if(!v) return t;

    b = v->m_r;
    c = p->m_r; d = t->m_r;
    v->m_r = p;
    p->m_l = b;
    p->m_r = t;
    t->m_l = c;
    t->m_r = d;

    return v;
}

SplayTree
RR(SplayTree t) {
    t->m_r = R(t->m_r);
    return R(t);
}

SplayTree
RR_tarjain(SplayTree t) {
    PNode a, c, d;
    SplayTree p, v;
    p = t->m_r;
    if(!p) return t;
    v = p->m_r;
    if(!v) return t;
    a = v->m_l;
    c = p->m_l;
    d = t->m_l;

    v->m_l = p;
    p->m_l = t;
    p->m_r = a;
    t->m_l = d;
    t->m_r = c;
    return v;
}

SplayTree
LR(SplayTree t) {
    SplayTree p,v;
    PNode a, b, c, d;
    p = t->m_l;
    if(!p) return t;
    v = p->m_r;
    if(!v) return t;

    a = v->m_l; b = v->m_r;
    c = p->m_l; d = t->m_r;
    v->m_l = p;
    p->m_l = c;
    p->m_r = a;
    v->m_r = t;
    t->m_l = b;
    t->m_r = d;
    return v;
}

SplayTree
RL(SplayTree t) {
    SplayTree p, v;
    PNode a, b, c, d;
    p = t->m_r;
    if(!p) return t;
    v = p->m_l;
    if(!v) return t;

    a = v->m_l; b = v->m_r;
    c = p->m_r; d = t->m_l;
    v->m_l = t;
    t->m_l = d;
    t->m_r = a;
    v->m_r = p;
    p->m_l = b;
    p->m_r = c;
    return v;
}

/*!单旋*/
SplayTree
L(SplayTree t) {
    SplayTree l = t->m_l;
    if(!l) return t;
    t->m_l = l->m_r;
    l->m_r = t;
    return l;
}

/*!单旋*/
SplayTree
R(SplayTree t) {
    SplayTree r = t->m_r;
    if(!r) return t;
    t->m_r = r->m_l;
    r->m_l = t;
    return r;
}

SplayTree
splay_topdown(int k, SplayTree t) {
    Node l, r;
    PNode tmp, tmp2;
    l.m_l = l.m_r = NULL;
    r.m_l = r.m_r = NULL;

    if(!t) {
        return t;
    }

    for(;;) {
        if(k == t->m_val){
            break;
        } else if(k < t->m_val) {
            if(t->m_l == NULL) break;
            if(k < t->m_l->m_val) {
                tmp = t->m_l;
                t->m_l = tmp->m_r;
                tmp->m_r = t;
                /*!重新设置根节点*/
                t = tmp;
            }
            if(t->m_l == NULL) break;
            tmp2 = t->m_l;
            if(r.m_r) {
                /*!合并右侧的大树*/
                tmp = r.m_r;
                while(tmp->m_l) {
                    tmp = tmp->m_l;
                }
                t->m_l = NULL;
                tmp->m_l = t;
            } else {
                /*!将树移动到右侧*/
                r.m_r = t;
            }
            t = tmp2; /*!mid树变成左子树*/
            r.m_l = NULL;
        } else if(k > t->m_val) {
            if(t->m_r == NULL) break;
            if(k > t->m_val) {
                tmp = t->m_r;
                t->m_r = tmp->m_l;
                tmp->m_l = t;
                /*!重新设置根节点*/
                t = tmp;
            }
            if(t->m_r == NULL) break;
            tmp2 = t->m_r;
            if(l.m_l) {
                /*!合并左侧的大树*/
                tmp = l.m_l;
                while(tmp->m_r) {
                    tmp = tmp->m_r;
                }
                t->m_r = NULL;
                tmp->m_r = t;
            } else {
                /*!将树移动到左侧*/
                l.m_l = t;
            }
            t = tmp2;
            l.m_r = NULL;
        }
    }

    /*!重新组织 reasemembl*/
    if(l.m_l) {
        l.m_l->m_r = t->m_l;
        t->m_l = l.m_l;
    }
    if(r.m_r) {
        r.m_r->m_l = t->m_r;
        t->m_r = r.m_r;
    }

    return t;
}

SplayTree
splay_eachLayer(int k, SplayTree t) {
    return t;
}

SplayTree
splay_tarjan(int k, SplayTree t) {
    return t;
}


#define TOPDOWN
SplayTree
splay(int k, SplayTree t) {
    SplayTree (*fp)(int, SplayTree) = NULL;
#if defined(TOPDOWN)
    fp = splay_topdown;
#elif defined(EACHLAYER)
    fp = splay_eachLayer;
#else
    fp = splay_tarjan;
#endif

    return (*fp)(k, t);
}

SplayTree 
insert(int k, SplayTree t) {
    SplayTree n;
    /*!返回的根节点是最接近k的位置*/
    t = splay(k, t);
    if(!t) {
        t = (SplayTree)malloc(sizeof(Node));
        t->m_val = k;
        t->m_l = t->m_r = NULL;
        return t;
    }

    if(t->m_val == k) {
        return t;
    } else {
        n = (SplayTree)malloc(sizeof(Node));
        n->m_val = k;
        n->m_l = n->m_r = NULL;

        if(k < t->m_val) {
            n->m_l = t->m_l;
            n->m_r = t;
            t->m_l = NULL;
        } else {
            n->m_r = t->m_r;
            n->m_l = t;
            t->m_r = NULL;
        }
        t = n;
    }

    return t;
}

SplayTree
delete(int k, SplayTree t) {
    return t;
}

void
show(SplayTree t, const char *s) {
    printf("%s:", s);
    showTree(t);
    printf("\n");
}

SplayTree
emptyTree(SplayTree t) {
    if(!t) return t;
    emptyTree(t->m_l);
    emptyTree(t->m_r);
    free(t);

    return NULL;
}

int
main(int argc, char *argv[]) {
    int i, j;
    int data[NUMS];
    SplayTree t ;

    (void)argc;
    (void)argv;
    for(i=0; i<NUMS; ++i) data[i] = i+1;
    random_data(data, NUMS);

    t = NULL;
    for(i=0; i<NUMS; ++i) {
        t = insert(data[i], t);
        show(t, "SplayTree");
    }

    t = emptyTree(t);
    return 0;
}


