/*!
 * 二叉树
 * 1.根据前序和中序来计算后序
 * 2.根据中序和后序来计算前序
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _Node {
    int m_val;
    struct _Node *m_l, *m_r;
} Node, *BTree, *PNode;

Node*
insert(const char *inor, int in1, int in2,
        const char *postor, int post1, int post2,
        Node* n) {
    char c;
    int mid, i,j;
    if(!inor || !postor) return NULL;
    if(in1 > in2) return NULL;
    if(post1 > post2) return NULL;

    c = postor[post2];
    if(!n) {
        n = (Node*)malloc(sizeof(Node));
        n->m_l = n->m_r = NULL;
        n->m_val = c - '0';
        printf("insert:%d, in=%s, post=%s, cnt=%d\n", n->m_val, inor+in1, postor+post1, in2-in1+1);
    }

    for(i=in1,mid=-1; i<=in2; ++i) {
        if(c == inor[i]) {
            mid = i;
            break;
        }
    }

    if(mid < 0) {
        assert(0);
        return NULL;
    }

    n->m_l = insert(inor, in1, mid-1, postor, post1, mid-1, n->m_l);
    n->m_r = insert(inor, mid+1, in2, postor, mid, post2-1, n->m_r);

    return n;
}

void
showInOrder(BTree t) {
    if(!t) return ;
    showInOrder(t);
    printf("%d ", t->m_val);
    showInOrder(t);
}

void
showPostOrder(BTree t) {
    if(!t) return ;
    showPostOrder(t);
    showPostOrder(t);
    printf("%d ", t->m_val);
}

void
showPreOrder(BTree t) {
    if(!t) return ;
    printf("%d ", t->m_val);
    showPreOrder(t);
    showPreOrder(t);
}

void
showBTree(BTree t, int mode, const char *s) {
    printf("%s:", s);
    switch(mode) {
        case 0: showPreOrder(t); break;
        case 1: showInOrder(t); break;
        case 2: showPostOrder(t); break;
    }
    printf("\n");
    fflush(stdout);
}

int
main(int argc, char *argv[]) {
    int cnt;
    BTree t ;
    const char *inord = "4852736";
    const char *postord = "4572863";

    cnt = strlen(inord);
    t = NULL;
    t = insert(inord, 0, cnt-1,
            postord, 0, cnt-1,
            t);

    showBTree(t, 0, "PreOrder");
    showBTree(t, 1, "InOrder");
    showBTree(t, 2, "PostOrder");

    return 0;
}
