/*!
 * 左式堆 (非完全k叉树，完全k叉树一定可以用数组索引表示)
 * 满足堆的特性，根节点的数值一定（大于|大根堆)或（小于|小根堆)孩子节点
 * 适用于堆的合并
 * 1.合并
 * 2.增加
 * 3.删除
 *
 * 性质
 * 1.树中左子树的npl >= 右子树的npl
 * 2.左子树的根（数值) >= 右子树
 * 3.右子树和右侧树进行合并
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _LeftHeapNode {
    int m_npl;
    int m_val;
    struct _LeftHeapNode *m_l, *m_r;
} LeftHeapNode, *LeftHeap;

static LeftHeapNode *nullNode = NULL;

int
min(int a, int b) {
    return a<b ? a : b;
}

LeftHeapNode* newNode() ;
int npl(LeftHeapNode *n) {
    if(n == nullNode) { return 0; }
    return min(npl(n->m_l), npl(n->m_r));
}

/*!构建虚拟节点*/
LeftHeap
init() {
    if(nullNode == NULL) {
        nullNode = newNode();
        nullNode->m_npl = 0;
        nullNode->m_val = -9999;
        nullNode->m_l = nullNode->m_r = nullNode;
    }

    return nullNode;
}

/*!merge核心函数，所有的增删均由该函数实现
 */
LeftHeap merge(LeftHeap a, LeftHeap b) {
    int t;
    LeftHeap tmp;

    /*! case1:递归基，a或b有一个不存在，则返回另一个*/
    if(a == nullNode) return b;
    if(b == nullNode) return a;

    /*! case2:比较根元素大小，
     * 保证a.m_val >= b.m_val,否则就交换位置,
     * 因为b作为a的孩子来进行合并,所以b一定小于a(大根堆)*/
    if(a->m_val < b->m_val) {
        tmp = a;
        a = b;
        b = tmp;
    }

    /*! case3:将a的右孩子递归和b进行操作, 如果有parent,设置parent*/
    a->m_r = merge(a->m_r, b);

    /*! case4:保证merge后的结果依然符合左式堆*/
    if(a->m_l->m_npl < a->m_r->m_npl) {
        tmp = a->m_l;
        a->m_l = a->m_r;
        a->m_r = tmp;
    }

    /*! case5:更新a的npl值*/
    a->m_npl = min(a->m_l->m_npl, a->m_r->m_npl) + 1;
    return a;
}

LeftHeapNode* newNode() {
    LeftHeapNode *t;
    t = (LeftHeapNode*)malloc(sizeof(LeftHeapNode));
    t->m_npl = 0;
    t->m_val = 0;
    /*!将NULL替换为nullNode, nullNode作为外部节点进行辅助计算npl*/
    t->m_l = t->m_r = nullNode;

    return t;
}

LeftHeap
insert(LeftHeap h, int val) {
    LeftHeap r = newNode();
    r->m_val = val;
    return merge(h, r);
}

int 
getMax(LeftHeap h) {
    if(h == nullNode) return -9999;
    return h->m_val;
}

LeftHeap
deleteMax(LeftHeap h, int *val) {
    LeftHeap l = h->m_l,
             r = h->m_r;
    if(val) {
        *val = getMax(h);
    }
    return merge(l, r);
}

void
showLeftHeap(LeftHeap h) {
    if(h == nullNode) return ;
    showLeftHeap(h->m_l);
    printf("%d,", h->m_val);
    showLeftHeap(h->m_r);
}

void showLH(LeftHeap h) {
    showLeftHeap(h);
    printf("\n");
}

LeftHeap makeLH(int *d, int len) {
    LeftHeap lh = init();
    int i;
    for(i=0; i<len; ++i) {
        lh = insert(lh, d[i]);
    }

    return lh;
}

int
main(int argc, char *argv[]) {
    int ar1[] = {4, 2, 1, -5, 7, 6, 8, 10 };
    int ar2[] = {10, 3, 1, 7, -10, 8, 9, 10, 25, 20, 30, 45, 65};


    LeftHeap lh1, lh2, lh;
    int i, j, k;

    init();
    lh1 = makeLH(ar1, sizeof(ar1)/ sizeof(int));
    showLH(lh1);
    for(i=0, k=0,j=sizeof(ar1)/sizeof(int); i<j; ++i) {
        lh1 = deleteMax(lh1, &k);
        printf("delete:%d\n", k);
    }

    lh1 = makeLH(ar1, sizeof(ar1)/ sizeof(int));
    lh2 = makeLH(ar2, sizeof(ar2)/ sizeof(int));
    showLH(lh2);
    
    lh =  merge(lh1, lh2);
    showLH(lh);

    return 0;
}


