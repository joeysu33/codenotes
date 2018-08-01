/*!
 * 跳表 
 * 一种数据结构简单，但是可以和平衡树的性能进行对标的链式结构
 * 多联链表
 *
 * -INT_MAX ----------------------------------------------- INT_MAX
 * -INT_MAX ---------------26-------33-------------80----86 INT_MAX
 * -INT_MAX ----9----------26-------33-------------80----86 INT_MAX
 * -INT_MAX ----9----------26-------33-35-40-------80----86 INT_MAX
 * -INT_MAX 3 8 9 10 15 20 26 28 31 33 35 40 44 49 80 85 86 INT_MAX
 *
 *  resdis和levelDB均使用了跳表
 *  跳表也是CBA式算法的一种 Classify Base of Association (基于关联的数据结构)
 *  K-V (词典),主要实现方式有平衡树(AVL树, RB树, B树, B+树, B*树), 以及哈希表(MAD hashcode = (hashcode *a + b) % M;
 *  参阅:skiplist在redis中主要应用于sorted set的实现
 *       levelDB是Google对轻量K-V型数据库的实现
 *
 *  跳表的性质:
 *  1.跳表的最底层包含了所有的集合元素
 *  2.跳表的最底层元素的数据为有序
 *  3.跳表的上一层始终是下一层的子集
 *  4.跳表的一列表征的元素相同
 *  5.跳表的最左侧代表无限小，最右侧代表无限大
 *
 *  跳表的实现原理，利用纵向的数据链表，将其上升为索引，链表的元素
 *  增高（也成为塔长高），利用了随机分布原理, (rand() % 0x1),理想
 *  状态应该随着塔的增高，每一层的元素是下一层的一半，而上层的元素
 *  始终作为索引，参数数据的增删查找。
 *
 *  实现:
 *  1.使用二联链表, 单向索引，总是从左上开始往右下角进行索引
 *  struct SkipListNode {
 *      int k;
 *      T value;
 *      struct SkipListNode *m_next;
 *      struct SkipListNode *m_down;
 *  }; //在索引的时候效率很低，直接采用四联链表 
 *
 *  2.使用四联链表，双向索引，总是从左上角开始往右下角进行索引
 *  struct SkipListNode {
 *      int k;
 *      T value;
 *      struct SkipListNode *m_top, *m_bottom;
 *      struct SkipListNode *m_prev,*m_next;
 *  };
 *
 *  跳表的平均复杂度O(lgN),跳表的核心实现原理是利用空间来换取时间(重复纵向数据单元)
 */
 

#include <stdio.h>
#include <stdlib.h> //构建随机数来让塔长高rand()
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>

typedef struct Entry {
    int m_k;
    int m_v;
} Entry, *EntryPtr;

typedef struct SkipListNode {
    Entry *m_ent;
    struct SkipListNode *m_next , *m_down, *m_top, *m_prev;
} *SkipListNodePosi, KLN, SkipListNode;

SkipListNodePosi
goBottom(SkipListNodePosi i) ;
SkipListNodePosi
goTop(SkipListNodePosi i);

SkipListNode*
makeNode() {
    SkipListNode *n = (SkipListNode*) malloc(sizeof(SkipListNode));
    assert(n);

    n->m_ent = NULL;
    n->m_next = n->m_down = NULL;
    n->m_top = n->m_prev = NULL;
    return n;
}

EntryPtr
makeEntry() {
    EntryPtr e = (EntryPtr)malloc(sizeof(Entry));
    assert(e);

    e->m_k = -1;
    e->m_v = -1;
    return e;
}

EntryPtr
makeEntry2(int k, int v) {
    EntryPtr e = makeEntry();
    e->m_k = k; e->m_v = v;
    return e;
}

EntryPtr
makeEntry1(int k) {
    return makeEntry2(k, -1);
}

SkipListNode*
newNode2(EntryPtr ent, SkipListNodePosi next, SkipListNodePosi down)  {
    SkipListNode  *n = makeNode();
    n->m_ent  = ent;
    n->m_next = next;
    n->m_down = down;
    n->m_prev = NULL;
    n->m_top = NULL;
    return n;
}

SkipListNode*
newNode(int k, int v, SkipListNodePosi next, SkipListNodePosi down) {
    return newNode2(makeEntry2(k, v), next, down);
}

SkipListNode*
newNode3(int k, int v) {
    return newNode(k, v, NULL, NULL);
}

SkipListNode*
newNode4(EntryPtr ent) {
    return newNode2(ent, NULL, NULL);
}

void
freeEntry(EntryPtr e) {
    if(e) free(e);
}

//释放Entry和SkipListNode,最低一层调用
void
freeNode(SkipListNodePosi n) {
    freeEntry(n->m_ent);
    free(n);
}

//仅仅释放SkipListNode,非最底层调用
void
freeNode1(SkipListNodePosi n) {
    free(n);
}

int
towerUp() {
    if(rand() & 0x1) return 1;
    return 0;
}

typedef struct SkipList {
    //搜索指定的k
    SkipListNodePosi (*search)(struct SkipList* list, int k);
    //存入kv
    SkipListNodePosi (*put)(struct SkipList* list, int k, int v);
    //根据k来取值
    EntryPtr (*get)(struct SkipList* list, int k);
    //根据k来取值
    int (*getv) (struct SkipList* list, int k);
    int (*hasKey) (struct SkipList* list, int k);
    int (*removeKey) (struct SkipList* list, int k);

    //表大小
    int (*size)(struct SkipList *list);
    //表是否空
    int (*empty)(struct SkipList *list);

    //表头
    SkipListNodePosi (*first)(struct SkipList *list);
    //表尾
    SkipListNodePosi (*last)(struct SkipList *list);

    //-INT_MAX +INT_MAX
    //m_header始终指向Skiplist的左上角,
    //m_tail始终指向Skiplist的右上角.
    SkipListNodePosi m_header, m_tail;
    //元素个数
    int m_size;
    //跳表的高度
    int m_height;
} SkipList, *SkipListPtr;

/*!
 * 搜索出来的结果小于或等于k, 类似lowerBound
 * k >= search(k)
 */
SkipListNodePosi 
search (struct SkipList* list, int k) {
    if(!list) return NULL;
    SkipListNodePosi i = list->m_header, j, m;
    //posi始终位于左上角,顺着链表往右下角走动
    //i = (*list->first)(list);

    //水平方向移动, 先走到最右侧，然后往下走
    //理论上不可能走到INT_MAX,默认认为键值k，一定小于INT_MAX,++++++++
    /*!
    while(i && k > i->m_ent->m_k) i = i->m_next;
    for(; i;) {
        j = i;
        while(k > j->m_ent->m_k && j->m_next) j = j->m_next;
        i = i->m_down;
    }
    */
    //因为k值不可能比-INT_MAX小，比INT_MAX大
    while(1) {
        while(i && k > i->m_ent->m_k) {
            i = i->m_next;
        }

        while(i && k < i->m_ent->m_k) {
            i = i->m_prev;
        }

        assert(i);
        //再往下走
        if(!i->m_down) return i;
        i = i->m_down;
    }

    return list->m_tail;
}

int
hasKey(struct SkipList* list, int k) {
    SkipListNodePosi i = search(list, k);
    return (i->m_ent->m_k == k) ;
}

//将当前的节点位置进行上升（塔长高)
//插入方法，如果升高一层，则向临近方向（左边或右边进行检索，如果检索到-INT_MAX或INT_MAX则停止)

SkipListNodePosi
growNode(SkipListNodePosi n, struct SkipList *list) {
    if(!n || !list) return n;

    SkipListNodePosi i, j, k, i1, i2;
    SkipListNodePosi header = list->m_header, tail = list->m_tail;
    i = newNode4(n->m_ent); //复用Entry的数据,但不释放，仅释放一次

    //垂直方向
    i->m_down = n; 
    n->m_top = i;

    //水平方向,向左走，探测第一个已经存在的有top的节点
    //左右方向进行探测
    //左上查找
    j = n->m_prev;
    while(j && !j->m_top) {
        j = j->m_prev;
    }

    //L找到
    if(j && j->m_top) { 
        i1 = j->m_top;
    } else {
        //将header升高一层
        k = newNode4(header->m_ent);
        header->m_top = k;
        k->m_down = header;
        list->m_header = k;
        i1 = k;
    }

    //左边根本就没有探测查找到，右侧开始继续查找
    //右上查找
    j = n->m_next;
    while(j && !j->m_top) {
        j = j->m_next;
    }

    //R找到
    if(j && j->m_top) {
        i2 = j->m_top;
    } else {
        //将tail升高一层
        k = newNode4(tail->m_ent);
        tail->m_top = k;
        k->m_down = tail;
        list->m_tail = k;
        i2 = k;
        list->m_height++;
        printf("升高一层\n");
    }

    assert(i1 && i2);
    i1->m_next = i;
    i->m_prev = i1;

    i->m_next = i2;
    i2->m_prev = i;

    return i;
}

SkipListNodePosi
goTop(SkipListNodePosi i) {
    if(!i) return i;
    while(i->m_top) i = i->m_top;
    return i;
}

SkipListNodePosi
goBottom(SkipListNodePosi i) {
    if(!i) return i;
    while(i->m_down) {
        i = i->m_down;
    }

    return i;
}

SkipListNodePosi
put(struct SkipList* list, int k, int v) {
    SkipListNodePosi i = search(list, k), j;
    SkipListNodePosi n = newNode3(k, v);

    //左右都有边界
    assert(i);
    i = goBottom(i);

    //水平方向(横向), 四次赋值
    /*
    j = i->m_prev;
    j->m_next = n;
    n->m_prev = j;
    n->m_next = i;
    i->m_prev = n;
    */

    j = i->m_next;
    n->m_prev = i;
    i->m_next = n;
    n->m_next = j;
    j->m_prev= n;

    //垂直方向(纵向)
    while(towerUp()) {
        n = growNode(n, list);
    }

    return n;
}

void
removePosi(SkipListNodePosi i, struct SkipList *list) {
    if(!i || !list) return ;
    i = goTop(i);

    //自上而下，逐一进行断开操作,如果断开之后，header---tail,则移除该层
    SkipListNodePosi j, k, n;
    while(i->m_down) {
        j = i->m_prev;
        k = i->m_next;

        n = i;
        i = i->m_down;
        /*!
         * header和tail直线连接，删除该行,且该层不是最后一层
         */
        if(!j->m_prev && !k->m_next && j->m_down) {
            assert(k->m_down); //k和j在同一层
            assert(list->m_height > 1); //塔的高度>1

            //重新设置header和tail
            list->m_header = j->m_down;
            list->m_tail = k->m_down;

            freeNode1(j); freeNode1(k); freeNode1(i);
            i->m_top = NULL;
            list->m_height--;
            printf("降低一层\n");
        } else {
            j->m_next = k;
            k->m_prev = j;
            freeNode1(n);
        }
    }

    //可以确定已经退化到最后一层,直接删除即可
    j = i->m_prev;
    k = i->m_next;
    j->m_next = k;
    k->m_prev = j;
    freeNode1(i);
}

EntryPtr 
get(struct SkipList* list, int k) {
    SkipListNodePosi i = search(list, k);
    i = goBottom(i);
    return i->m_ent;
}

int
getv(struct SkipList* list, int k) {
    EntryPtr e = get(list, k);
    if(!e) return -1;
    return e->m_v;
}

int
removeKey(struct SkipList* list, int k) {
    int r ;
    SkipListNodePosi i = search(list, k);
    i = goBottom(i);

    if(!i) return -INT_MAX;
    r = i->m_ent->m_v;
    removePosi(i, list);
    return r;
}

int
size(struct SkipList* list)  {
    if(!list) return 0;
    return list->m_size;
}

int 
empty(struct SkipList* list) {
    if(!list) return 1;
    return size(list) == 0;
}

SkipListNodePosi 
first(struct SkipList* list) {
    if(!list) return NULL;
    return list->m_header;
}

SkipListNodePosi
last(struct SkipList *list) {
    if(!list) return NULL;
    return list->m_tail;
}

int
height(struct SkipList *list) {
    if(!list) return 0;
    return list->m_height;
}

SkipList*
init(struct SkipList *list) {
    if(!list) return list;
    list->m_size = 0;
    list->m_height = 0;
    list->m_header = newNode3(-INT_MAX, -INT_MAX);
    list->m_tail = newNode3(INT_MAX, INT_MAX);

    //初始化header <----> tail
    list->m_header->m_next = list->m_tail;
    list->m_tail->m_prev = list->m_header;

    //====初始化成员函数====
    list->search = search;
    list->put = put;
    list->get = get;
    list->getv = getv;
    list->size = size;
    list->empty = empty;
    list->first = first;
    list->last = last;
    list->hasKey = hasKey;
    list->removeKey = removeKey;

    return list;
}

void
clean(struct SkipList *list) {
    if(!list) return ;
    SkipListNodePosi i = list->m_header, j, k;

    /*! 逐渐降低塔的高度，来释放数据结构 */
    //自上而下，自左而右
    while(i->m_down) {
        j = i;
        i = i->m_down;

        while(j->m_next) {
            k = j;
            j = j->m_next;
            freeNode1(k);
        }
        freeNode1(j); //最后一个j
        list->m_height--;
        printf("降低一层\n");
    }

    //最后一层，需要删除Entries
    list->m_header = i;
    i = i->m_next;
    //删除中间部分
    while(i->m_next) {
        j = i;
        i = i->m_next;
        freeNode(j); //删除包含Entry
    }
    list->m_tail = i;
}

void
showList(struct SkipList *list) {
    SkipListNodePosi i = list->m_header, j, k;
    while(i) {
        j = i;
        while(j) {
            printf("(%d,%d) ", j->m_ent->m_k, j->m_ent->m_v);
            j = j->m_next;
        }
        printf("\n---------------------------------------------------------------------------------------\n");
        i = i->m_down;
    }
    printf("\n\n");
}

int
main(int argc, char *argv[]) {
    SkipList list, *plist;
    srand(time(NULL));

    int i, j, k;
    j = 10;
    plist = init(&list); /*! plist == &list */

    showList(plist);
    for(i=0; i<j; ++i) {
        k = i+10;
        put(plist, k, k*2) ;
    }

    showList(plist);
    for(i=0; i<j; ++i) {
        k = i+10;
        printf("get(%d)=%d\n", k,getv(plist, k));
    }

    clean(plist);
    return 0;
}



