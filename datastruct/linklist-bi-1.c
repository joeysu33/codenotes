/*!
 * 双向链表 (使用头指针版本)
 */
#include "common.h"

typedef int ElType ;
typedef struct _Node{
    ElType m_data;
    struct _Node *m_next ;
    struct _Node *m_prev;
}Node, *DLinkList, *PNode;

/*!
 * 初始化构建一个头指针
 * 使用destory来删除头指针
 */
void init_list(DLinkList* list) {
    *list = (DLinkList)malloc(sizeof(Node));
}

void push_back(DLinkList list, ElType value) {
    if(!list) return ;
}

void push_front(DLinkList list, ElType value) {
}

bool pop_back(DLinkList list,ElType *value) {
}

bool pop_front(DLinkList list, ElType *value) {
}

Node* next(Node* n) {
    if(!n) return NULL;
    return n->m_next;
}

Node* prev(Node* n) {
    if(!n) return NULL;
    return n->m_prev;
}

void remove_node(DLinkList list,Node* n) {
    DLinkList i=list, j;
    if(!list || !n) return ;
    i=list->m_next;
    while(i) {
        if(i == n) {
            if(i->m_next) {
                i->m_prev->m_next = i->m_next;
                i->m_next->m_prev = i->m_prev;
            }
            fprintf(stdout, "free node:0x%08x value:%d", *(unsigned int*)i, i->m_data);
            free(i);
            break;
        }
        i=i->m_next;
    }
}

void remove_node_by_value(DLinkList list,ElType value) {
    if(!list) return ;
}

/*!
 * 删除所有，包含头指针
 */
void destory_list(DLinkList* list) {
    DLinkList i=*list, j=NULL;
    if(!i) return ;
    while(i) {
        j=i;
        i=i->m_next;
        fprintf(stdout, "free node:0x%08x value:%d", *(unsigned int*)j, j->m_data);
        free(j);
    }
}

unsigned int get_size(DLinkList list) {
    int i=0; 
    if(!list) return 0;
    while(list->m_next) {
        i++;
        list=list->m_next;
    }
    return i;
}

int main() {
    return 0;
}

