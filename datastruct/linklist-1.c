/*!
 * 单链表、双链表的使用
 * 无头结点的实现情况
 * 需要考虑特殊条件的处理
 * 1.无任何节点(NULL)
 * 2.只有一个节点
 * 3.节点的访问n n->next，判断条件也只有这两种
 */

#include "common.h"

typedef int ElType;
typedef struct Node{
    ElType m_value;
    struct Node* m_next;
} *LinkList, Node;

Node *newNode(ElType v) {
    Node * n = (Node*) malloc(sizeof(Node));
    if(!n) {
        assert(false);
        return NULL;
    }
    n->m_value = v;
    n->m_next = NULL;
    return n;
}

Node* getFirst(LinkList list) ;
Node* getLast(LinkList list) ;

Node *newNodeV2() {
    return newNode((ElType)0);
}

void push_back(LinkList* list, ElType value) {
    LinkList l;
    if(!(*list)) {
        *list = newNode(value);
        return;
    } 

    l = *list;
    Node* n = getLast(l);
    assert(n);
    n->m_next = newNode(value);
}

bool pop_back(LinkList* list, ElType *value) {
    Node *c= *list,*p = *list ;
    if(!(*list) || !value) return false;

    while(c->m_next) {
        p = c;
        c = c->m_next;
    }
    if(c == p) {
        free(*list);
        *value = (*list)->m_value;
        *list = NULL;
    } else {
        *value = p->m_next->m_value;
        free(p->m_next);
        p->m_next = NULL;
    }

    return true;
}

void push_front(LinkList* list, ElType value) {
    Node *n1,*n2;
    if(!(*list)) {
        *list = newNode(value);
        return;
    }
    n1 = getFirst(*list);
    n2 = newNode(value);
    if(!n2) return ;
    n2->m_next = n1;
    *list = n2;
} 

bool pop_front(LinkList* list, ElType *value)
{
    if(!(*list) || !value) return false;
    Node *n = *list;
    *value = n->m_value;
    *list = n->m_next;
    free(n);
    return true;
}

Node* getLast(LinkList list) {
    if(!list) return NULL;
    Node *p = list;
    while(list) {
        p = list;
        list = list->m_next;
    }
    return p;
}

Node* getFirst(LinkList list) {
    if(!list) return NULL;
    return list;
}

void dump(LinkList list) {
    if(!list) {
        fprintf(stdout, "<empty>\n");
        return ;
    }
    int n=0;
    while(list) {
        fprintf(stdout, "%d,",list->m_value);
        n++;
        list = list->m_next;
    }
    fprintf(stdout, " count:%d\n",n);
}

void clear(LinkList *list) {
    Node *n=*list,*t;
    if(!(*list)) return ;
    while(n) {
        t = n;
        n=n->m_next;
        free(t);
    }
    *list = NULL;
}

#define PUSH_BACK(n) push_back(&list, n)
#define POP_BACK(n) pop_back(&list,n)
#define PUSH_FRONT(n) push_front(&list, n)
#define POP_FRONT(n) pop_front(&list, n)

int main() {
    int i=0;
    ElType n;
    LinkList list=NULL;

    PUSH_BACK(10);
    PUSH_BACK(20);
    PUSH_BACK(8);
    PUSH_BACK(7);
    dump(list);

    assert(POP_BACK(&n));
    assert(n == 7);
    dump(list);
    PUSH_FRONT(1000);
    PUSH_FRONT(2000);
    PUSH_FRONT(3000);
    assert(POP_FRONT(&n));
    assert(n == 3000);
    dump(list);

    {
        i=0;
        while(list) {
            pop_back(&list, &n);
            i++;
        }
        assert(i==5);
    }

    PUSH_BACK(100);
    PUSH_BACK(400);
    dump(list);

    {
        i=0;
        while(list) {
            pop_front(&list, &n);
            i++;
        }
        assert(i==2);
    }

    PUSH_BACK(76);
    PUSH_BACK(56);
    PUSH_BACK(42);
    dump(list);

    clear(&list);
    dump(list);

    return 0;
}


