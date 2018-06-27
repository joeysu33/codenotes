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
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

typedef int Type;

#define INVALID_VALUE INT_MIN
#define ALLOWED_IMBALANCE 1  /*!允许的不平衡最大值*/

typedef struct _AVLNode {
    Type m_elem;
    int m_h;
    struct _AVLNode *m_l, *m_r;
} AVLNode, *AVLTree, *AVLPosition;

int
max(int a, int b) {
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
    if(t->m_elem < e) {
        return find(e, t->m_l);
    } else if(t->m_elem > e) {
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
    if(!p) return p;
    /*!p的左边子树不平衡*/
    if(getHeight(p->m_l) - getHeight(p->m_r) > ALLOWED_IMBALANCE) {
        if(getHeight(p->m_l->m_l) > getHeight(p->m_l->m_r)) {
            p = LL(p);
        } else {
            p = LR(p);
        }
    /*!p的右边子树不平衡*/
    } else if(getHeight(p->m_r) - getHeight(p->m_l) > ALLOWED_IMBALANCE) {
        if(getHeight(p->m_r->m_r) > getHeight(p->m_r->m_l)) {
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
    } 

    /*!Ok, find it */
    if(t->m_l && t->m_r) {
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
        free(tmp);
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
}

int
main(int argc, char *argv[]) {
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


