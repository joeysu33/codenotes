/*!
 * AVL树
 * 1.自平衡二叉树，左右子树的高度差为-1, 0, 1
 * 2.AVL树平衡过程中的几种情况
 *   LL LR RL RR
 *   LL造成的不平衡进行右旋
 *   RR造成的不平衡进行左旋
 *   LR造成的不平衡进行先左旋后右旋
 *   RL造成的不平衡进行先右旋后左旋
 *
 *   *LL: 右旋
 *   *RR: 左旋
 *   *LR: 先左旋后右旋 => LR(p) <==> RR(p->l);LL(p);
 *   *RL: 先右旋后左旋 => RL(p) <==> LL(p->r);RR(p);
 *
 * 3.和二叉搜索树的操作基本相同，唯一区别在于操作完成之后需要进行调整(balance)
 *   和其他平衡树的形势相似,例如红黑树fixup
 * 4.AVL树是自底向上的来调整平衡
 *
 * 注意事项
 * 1.空指针情况的处理，例如AVLTree的初始化必须是NULL
 *   LL和RR操作的时候，如果子节点如空，则返回自身
 * 2.元素数值比较要注意，方向不要搞错，最好将element作为比较的左值
 *   这样避免出错
 * 3.空树的高度为-1,（有的教材也作为0 这样直接返回0即可, 最后一层的高是1)
 * 4.BST不支持重复数据（可以将重复数据单独用数据结构处理
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

typedef int Type;
static const int size = 2* 10;

#define INVALID_VALUE INT_MIN
#define ALLOWED_IMBALANCE 1  /*!允许的不平衡最大值*/

typedef struct _AVLNode {
    Type m_elem;
    int m_h;
    struct _AVLNode *m_l, *m_r;
} AVLNode, *AVLTree, *AVLPosition;
int max(int a, int b) {
    return (a>b)?a:b;
}

/*
int
abs(int a, int b) {
    int c = a-b;
    return c<0 ? -c : c;
}
*/

AVLTree
makeEmpty(AVLTree t) {
    if(!t) return NULL;
    makeEmpty(t->m_l);
    makeEmpty(t->m_r);
    free(t);
    return NULL;
}

Type
getValue(AVLPosition p) {
    return p ? p->m_elem : INVALID_VALUE;
}

int
getHeight(AVLPosition p) {
    /*! 对于空树的高度，有的定义为-1，有的定义为0,定义为-1，在递归的时候直接得到线段长度*/
    return p ? p->m_h : -1;
}

AVLPosition
findMin(AVLTree t) {
    if(!t) return NULL;
    if(!t->m_l) return t;
    return findMin(t->m_l);
}

AVLPosition
findMax(AVLTree t) {
    if(!t) return NULL;
    if(!t->m_r) return t;
    return findMax(t->m_r);
}

AVLPosition
find(const Type e, AVLTree t) {
    if(!t) return NULL;
    if(e < t->m_elem ) {
        return find(e, t->m_l);
    } else if(e > t->m_elem) {
        return find(e, t->m_r);
    }

    return t;
}

int
updateHeight(AVLPosition p) {
    if(!p) return -1; /*!语义保持一致 */
    return max(getHeight(p->m_l), getHeight(p->m_r)) + 1;
}

AVLPosition
LL(AVLPosition p) {
    AVLPosition l;
    if(!p) return p;
    l = p->m_l;
    if(!l) return p;
    p->m_l = l->m_r;
    l->m_r = p;

    /*!更新高度p, l*/
    p->m_h = updateHeight(p); /*!先更新子节点的高度, 顺序很重要*/
    l->m_h = updateHeight(l); /*!在更新父节点*/
    return l;  /*! New root */
}

AVLPosition
RR(AVLPosition p) {
    AVLPosition r;
    if(!p) return p;
    r = p->m_r;
    if(!r) return p;
    p->m_r = p->m_l;
    r->m_l = p;

    /*!更新高度p, r*/
    p->m_h = updateHeight(p); /*!先更新子节点, 顺序很重要*/
    r->m_h = updateHeight(r);
    return r; /*! New root */
}

AVLPosition
LR(AVLPosition p) {
    AVLPosition l;
    p->m_l = RR(p->m_l); /*! 先进行左旋，然后右旋*/
    return LL(p);
}

AVLPosition
RL(AVLPosition p) {
    AVLPosition r;
    p->m_r = LL(p->m_r); /*! 先进行右旋，然后左旋*/
    return RR(p);
}

AVLPosition
balance(AVLPosition p) {
    //return p;
    if(!p) return p;
    /*!p的左边子树不平衡*/
    if(getHeight(p->m_l) - getHeight(p->m_r) > ALLOWED_IMBALANCE) {
        if(getHeight(p->m_l->m_l) >= getHeight(p->m_l->m_r)) {
            p = LL(p);
        } else {
            p = LR(p);
        }
    /*!p的右边子树不平衡*/
    } else if(getHeight(p->m_r) - getHeight(p->m_l) > ALLOWED_IMBALANCE) {
        if(getHeight(p->m_r->m_r) >= getHeight(p->m_r->m_l)) {
            p = RR(p);
        } else {
            p = RL(p);
        }
    }

    /*!更新树的高度*/
    p->m_h = updateHeight(p);
    return p;
}

AVLPosition
insert(const Type e, AVLTree t) {
    if(!t) {
        t = (AVLPosition)malloc(sizeof(AVLNode));
        assert(t);
        t->m_h = 0;
        t->m_l = t->m_r = NULL;
        t->m_elem = e;
    } else if(e < t->m_elem) {
        t->m_l = insert(e, t->m_l);
    } else if(e > t->m_elem) {
        t->m_r = insert(e, t->m_r);
    } else {
        /*! Find it, do nothing*/
        ;
    }

    /*!make balance, after this, update t*/
    //t = balance(t);
    //return t;
    return balance(t);
}

AVLPosition
delete(const Type e, AVLTree t) {
    AVLPosition tmp;
    if(!t) return NULL;
    if(e < t->m_elem) {
        t->m_l = delete(e, t->m_l);
    } else if( e > t->m_elem) {
        t->m_r = delete(e, t->m_r);
    /*!Ok, find it, 不能始终调用这个，在相等的时候才能调用 */
    } else {
        if(t->m_l && t->m_r) { /*!-------这里应该是else，不能是if，如果是if始终都会调用--------*/
            tmp = findMin(t->m_r);
            t->m_elem = tmp->m_elem; /*!通过赋值已经将其删除*/
            t->m_r = delete(tmp->m_elem, t->m_r);
        } else {
            tmp = t;
            if(t->m_l) {
                t = t->m_l;
            } else if(t->m_r) {
                t = t->m_r;
            } else  {
                t = NULL;
            }
            if(size < 100)
                printf("----delete:%d\n", tmp->m_elem);
            free(tmp);
        }
    }

    /*!make balance, after this, update t*/
    //t = balance(t);
    //return t;
    return balance(t);
}

void
dumpInOrder(AVLTree t) {
    if(!t) return ;
    dumpInOrder(t->m_l);
    printf("%d ", t->m_elem);
    dumpInOrder(t->m_r);
}

void
dumpPreOrder(AVLTree t) {
    if(!t) return ;
    printf("%d ", t->m_elem);
    dumpInOrder(t->m_l);
    dumpInOrder(t->m_r);
}

void
dumpPostOrder(AVLTree t) {
    if(!t) return ;
    dumpInOrder(t->m_l);
    dumpInOrder(t->m_r);
    printf("%d ", t->m_elem);
}

void
dump3(int type, AVLTree t, const char *s) {
    if(!t || !s) return ;

    printf("%s:", s);
    switch(type) {
        case 0: dumpPreOrder(t); break;
        case 1: dumpInOrder(t); break;
        default: dumpPostOrder(t); break;
    }
    printf("\n");
}

void
dump2(AVLTree t, const char* s) {
    dump3(1, t, s);
    printf("\n");
}

int
litte_test(int argc, char *argv[]) {
    int i, j, k;
    Type arr[] = {35, 40, 0, 12, 9, 36, 37, 39, -5, 10, 99, 121 };
    const int cnt = sizeof(arr)/sizeof(Type);
    AVLTree t = NULL;
    for(i=0; i<cnt; ++i) {
        j = arr[i];
        t = insert(j, t);
    }
    dump2(t, "init");
    return 0;
}

void
random_shuff(int *p, int sz) {
    int i, j, k, m;
    for(i=0; i<sz* 4; ++i) {
        k=rand() % sz;
        j = rand() % sz;

        m = p[k];
        p[k] = p[j];
        p[j] = m;
    }
}

int
benchmark_test(int argc, char *argv[]) {
    int i, j, k, m;
    const int maxnum = 99999;
    int *ip;

    srand(time(NULL));
    ip = (int*)malloc(size *sizeof(int));
    assert(ip);

    AVLTree t = NULL;
    /*!随机增加数据，不能有重复数据*/
    for(i=0 ;i<size; ++i) {
        ip[i]=i;
    }

    /*!打散数据*/
    /*
    for(i=0; i<size * 4; ++i) {
        k=rand() % size;
        j = rand() % size;
        m = ip[k];
        ip[k] = ip[j];
        ip[j] = m;
    }*/
    random_shuff(ip, size);

    /*
    for(i=0; i<size; ) {
        j = rand() % maxnum ;

        m = 1;
        for(k=0;k<i;++k) {
            if(ip[k] == j) {
                m = 0; break;
            }
        }

        //无效数据，存在数据重复
        if(!m) continue;
        ip[i] = j;
        if(find(j, t)) {
            assert(0);
        }
        t = insert(j, t);
        if(!find(j, t)) {
            assert(0);
        }
        ++i;
    }
    */
    for(i=0; i<size; ++i) {
        j = ip[i];
        assert(!find(j, t));
        if(size < 100) {
            printf("%d, ", j);
        }
        t = insert(j, t);
        assert(find(j, t));
    }

    if(size < 100)
        dump2(t, "init");

    /*!随机删除数据*/
    printf("random delete:");
    random_shuff(ip, size);
    for(i=0; i<size; ++i) {
        k = ip[i];
        if(size < 100)
            printf("delete:[%d]\n ", k);
        if(!find(k, t)) {
            assert(0);
        }
        t = delete(k, t);
        if(find(k, t)) {
            assert(0);
        }
        if(size < 100)
            dump2(t, "delete");
    }

    printf("\n");
    fflush(stdout);

    free(ip);
    printf("finished\n");
    return 0;
}

int
main(int argc, char *argv[]) {
    int (*ptest)(int, char *[]);
    ptest = benchmark_test;
    return (*ptest)(argc, argv);
}


