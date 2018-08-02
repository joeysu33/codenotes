/*!
 * BinSearchTree
 */

#include <stdio.h>
#include <memory.h>
#include <stdlib.h> //malloc, rand, srand
#include <assert.h>
#include <time.h>

typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

struct TreeNode {
    int m_elem;
    SearchTree m_l;
    SearchTree m_r;
};

SearchTree 
makeEmpty(SearchTree t) {
    if(!t) return NULL;
    makeEmpty(t->m_l);
    makeEmpty(t->m_r);
    free(t);
    printf("empty:%d\n", t->m_elem);

    return NULL;
}

Position
getMin(SearchTree t) {
    if(!t) return NULL;
    if(!t->m_l) return t;
    return getMin(t->m_l);
}

Position
getMax(SearchTree t) {
    if(!t) return NULL;
    if(!t->m_r) return t;
    return getMax(t->m_r);
}

Position
find(int e, SearchTree t) {
    if(!t) return NULL;
    if(t->m_elem > e) {
        return find(e, t->m_l);
    } else if(t->m_elem < e) {
        return find(e, t->m_r);
    }

    return t;
}

SearchTree
insert(int e, SearchTree t) {
    /*! Create for new insert node */
    if(!t) {
        t = (SearchTree)malloc(sizeof(struct TreeNode));
        assert(t);

        /*! Initialization */
        t->m_elem = e;
        t->m_l = NULL;
        t->m_r = NULL;
        return t; /*!也可以不用写,因为t->m_elem == e */
    }

    if(t->m_elem > e) {
        t->m_l = insert(e, t->m_l);
    } else if(t->m_elem < e) {
        t->m_r = insert(e, t->m_r);
    }

    return t;
}

SearchTree
delete(int e, SearchTree t) {
    SearchTree st;
    if(!t) return NULL;

    if(t->m_elem > e) {
        t->m_l = delete(e, t->m_l);
    } else if(t->m_elem < e) {
        t->m_r = delete(e, t->m_r);
    } else {
        /*! Two child, 真实的删除元素已经被覆盖删除 */
        if(t->m_l && t->m_r) {
            /*! Find mininum of the right child tree  or find maxinum of the left child tree*/
            st = getMin(t->m_r);
            t->m_elem = st->m_elem; /*! Make sure search tree to be balance */
            t->m_r = delete(st->m_elem, t->m_r); /*! Delete right sub tree target */
        } else {
            /*! Less than 2 child, zero or one ,实际删除对应的节点*/
            st = t;
            if(t->m_l) 
                t = t->m_l;
            else if(t->m_r) 
                t = t->m_r;
            else 
                t = NULL; /*! No more child */
            printf("delete: %d\n", st->m_elem);
            free(st);
        }
    }

    return t; /*! return to yourself */
}

void
dump(SearchTree t) {
    if(!t) return ;
    dump(t->m_l);
    printf("%d ", t->m_elem);
    dump(t->m_r);
}

void
dump2(SearchTree t, const char *s) {
    if(!t || !s) return ;
    printf("%s:", s);
    dump(t);
    printf("\n");
}

int
main(int argc, char *argv[]) {
    int i, j;
    int arr[] = {7, 10, 1, 3, 4, 11, 38,46, 45, 10, 99};
    const int cnt = sizeof(arr)/sizeof(arr[0]);

    srand(time(NULL));
    SearchTree t;
    for(i=0, j=cnt; i<j; ++i) {
        t = insert(arr[i], t);
    }

    dump2(t,"initialize");
    for(i=0; i<6; ++i) {
        j = rand() % cnt;
        j = arr[j];
        printf("ready for delete:%d\n", j);
        delete(j, t);
        dump2(t, "after delete:");
    }

    return 0;
}


