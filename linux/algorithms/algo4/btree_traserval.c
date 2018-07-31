/*!
 * 二叉树的非递归遍历
 * Traversal (遍历)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _Node {
    int m_val;
    struct _Node *m_l, *m_r;
} Node, *Posi, *PNode, *BTree;

typedef void (*BTreeOpt) (PNode n);

//假定树上的节点元素不超过1024个
#define MAXN 1024 
#define ETYPE PNode
#include "stack.h"

PNode 
newNode(int val) {
    Node *n = (PNode)malloc(sizeof(Node));
    n->m_val = val;
    n->m_l = n->m_r = NULL;
    return n;
}

void
freeNode(PNode n) {
    free(n);
}

void
printNode(PNode n) {
    if(!n) return ;
    printf("%d ", n->m_val);
}

void
preOrderR(BTree t, BTreeOpt opt) {
    if(!t || !opt) return ;

    (*opt)(t);
    preOrderR(t->m_l, opt);
    preOrderR(t->m_r, opt);
}

void
inOrderR(BTree t, BTreeOpt opt) {
    if(!t || !opt) return ;

    inOrderR(t->m_l, opt);
    (*opt)(t);
    inOrderR(t->m_r, opt);
}

void
postOrderR(BTree t, BTreeOpt opt) {
    if(!t || !opt) return ;

    postOrderR(t->m_l, opt);
    postOrderR(t->m_r, opt);
    (*opt)(t);
}

void
layerOrderR(BTree t, BTreeOpt opt) {
}

/*
 * 非递归遍历-前序
 */
void
preOrder(BTree t, BTreeOpt opt) {
    PNode n;
    if(!t || !opt) return ;

    n = t;
    Stack s = makeS(MAXN), *stk = &s;
    pushS(stk, n);
    while(!emptyS(stk)) {
        n = popS(stk);
        (*opt)(n);

        if(n->m_r)
            pushS(stk, n->m_r);
        if(n->m_l)
            pushS(stk, n->m_l);
    }

    freeS(stk);
}

/*!
 * 非递归遍历-中序
 */
void
inOrder(BTree t, BTreeOpt opt) {
    PNode n;
    Stack s = makeS(MAXN), *stk = &s;
    if(!t || !opt) return ;

    n = t;
    /*!向栈里面插入元素，直到找到第一个最左元素*/
    while(n) {
        pushS(stk, n);
        n = n->m_l;
    }

    //现在栈中包含所有的左孩子以及每个左孩子的父亲节点，一直到根
    while(!emptyS(stk)) {
        n = popS(stk);
        (*opt)(n);

        /*!已经访问过了左孩子和根,现在访问右孩子*/
        if(n->m_r) {
            n = n->m_r;
            while(n) {
                pushS(stk, n);
                n = n->m_l;
            }
        }
    }

    freeS(stk);
}

/*!
 * 非递归遍历-后序
 */
void
postOrder_1(BTree t, BTreeOpt opt) {
    PNode n, p;
    if(!t || !opt) return ;
    Stack s = makeS(MAXN), *stk = &s;
    n = t;
    pushS(stk, n);
}

/*!
 * 非递归遍历-后序 (old)
 */
void
postOrder(BTree t, BTreeOpt opt) {
    PNode n, pre;
    if(!t || !opt) return ;
    Stack s = makeS(MAXN), *stk = &s;

    //n = t;
    /*!获取第一个元素*/
    /*while(n) {
        pushS(stk, n);
        n = n->m_l;
    }*/

    n = t; pre=NULL;
    pushS(stk, n);
    while(!emptyS(stk)) {
        n = topS(stk);
        //n = popS(stk);
        //存在右孩子要先处理,然后处理父节点对称的右子树
        /*while(n->m_r) {
            n = n->m_r;
            while(n) {
                pushS(stk, n);
                n = n->m_l;
            }
        }*/

        //不能退回到根节点，必须先处理父节点,这个时候topS必定是n的父节点
        //需要校验堆栈是否为空,因为要向上测试是否有没有处理的数据
        /*
        if(!emptyS(stk) && topS(stk)->m_r != n) {
            if(topS(stk)->m_r || (n == topS(stk)->m_l || !topS(stk)->m_l)) {
                n = topS(stk)->m_r;
                //继续从最左开始搜索
                while(n) {
                    pushS(stk, n);
                    n = n->m_l;
                }
            }
        }*/

        if((!n->m_l && !n->m_r) || (pre && (pre == n->m_l || pre == n->m_r))) {
            (*opt)(n);
            pre = n;
            n = popS(stk);
        } else {
            if(n->m_r)
                pushS(stk,n->m_r);
            if(n->m_l)
                pushS(stk,n->m_l);
        }


        /*! 出栈就处理 */
        //n = popS(stk);
        //(*opt)(n);
    }

    freeS(stk);
}

void
layerOrder(BTree t, BTreeOpt opt) {
}


#define LN(nd,v) \
    do {\
        nd->m_l = newNode(v);\
    }while(0)

#define RN(nd,v) \
    do {\
        nd->m_r = newNode(v);\
    }while(0)

BTree
makeTestBTree() {
    int vals[] = {8, 4, 3, 5, 12, 9, 33, 35, 46, 76};
    int count = sizeof(vals) / sizeof(int), i;
    PNode n = newNode(0), root = n;
    for(i=0; i<count; ++i) {
        if(rand() & 0x1) {
            n->m_l = newNode(vals[i]);
            n = n->m_l;
        } else {
            n->m_r = newNode(vals[i]);
            n = n->m_r;
        }
    }

    /*
    LN(n,8);RN(n,4);
    n = n->m_l;
    LN(n,3); RN(n,5);
    n = n->m_r;
    LN(n,12);RN(n,9);
    n = n->m_r;
    LN(n,33); RN(n,35);
    n = n->m_l;
    LN(n,46); RN(n,76);
    */

    return root;
}

#define CMPACC(t,ac, opt) \
    do {\
        printf("-------------------------\n");\
        ac(t, opt);\
        printf("\n");\
        ac##R(t, opt);\
        printf("\n");\
        printf("-------------------------\n");\
    }while(0)

int 
main(int argc, char *argv[]) {
    BTree t;
    srand(time(NULL));
    t = makeTestBTree();

    //preOrder(t, printNode);
    //preOrderR(t, printNOde);
    CMPACC(t, preOrder, printNode);
    CMPACC(t, inOrder, printNode);
    CMPACC(t, postOrder, printNode);

    //释放内存，最后操作根节点
    postOrder(t, freeNode);
    return 0;
}


