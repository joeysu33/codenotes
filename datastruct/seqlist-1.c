/*!
 * 顺序表
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "common.h"

//容器元素类型
typedef int ElType;

//容器
typedef struct {
    ElType *m_d;
    unsigned int m_size;
    unsigned int m_capacity;
} *SeqList, List;

#define INCREMENT_SIZE 10
#define INIT_SIZE 32

void push_back(SeqList *list, ElType e) {
    unsigned i, j;
    SeqList t1;
    ElType *pe ;

    if(!(*list)){
        *list = (SeqList)malloc(sizeof(List));
        if(!(*list)) return ;

        (*list)->m_d = NULL;
        (*list)->m_size = 0;
        (*list)->m_capacity = 0;
    }

    t1 = *list;
    if(!t1->m_d) {
        t1->m_d = (ElType*)malloc(sizeof(ElType) * INIT_SIZE);
        if(!t1->m_d) {
            return ;
        }
        t1->m_capacity = INIT_SIZE;
        t1->m_size = 0;
    } else {
        if(t1->m_capacity == t1->m_size) {
            i = t1->m_capacity;
            j = i + INCREMENT_SIZE;
            pe = (ElType*)malloc(sizeof(ElType) * j);
            if(!pe) return ;
            memcpy(pe, t1->m_d, sizeof(ElType) * t1->m_capacity);
            free(t1->m_d);
            t1->m_d = pe;
            t1->m_capacity = j;
            t1->m_size = i;
        }
    }

    t1->m_d[t1->m_size] = e;
    t1->m_size += 1;
}

bool pop_back(SeqList list, ElType *value) {
    if(!list || !value) {
        return false;
    }

    if(list->m_size == 0 ) {
        return false;
    }

    *value = list->m_d[list->m_size -1];
    list->m_size -= 1;
    return true;
}

ElType get(SeqList list, int index) {
    ElType t=0;
    if(!list) return t;
    if(index < 0 || list->m_size <=index) return t;
    return list->m_d[index];
}

void set(SeqList list, int index, ElType e) {
    if(!list) return ;
    if(index < 0 || index >= list->m_size)  return ;
    list->m_d[index] = e;
}

void clear(SeqList *list) {
    if(!(*list)) return ;
    free((*list)->m_d);
    free(*list);
    *list = NULL;
}

void dump(SeqList list) {
    int i;
    char chbuf[16];
    static char buffer[1024];
    buffer[0] = 0;
    for(i=0; i<list->m_size; ++i) {
        sprintf(chbuf, "%d", list->m_d[i]);
        strcat(buffer, chbuf);
        strcat(buffer, ",");
    }
    fprintf(stdout, "list-size:%d list-capacity:%d elements:%s\n", 
            list->m_size, list->m_capacity, buffer);
}

int main() {
    SeqList seq = NULL;
    ElType i;

    push_back(&seq, 1);
    dump(seq);
    push_back(&seq, 100);
    push_back(&seq, 30);
    dump(seq);

    assert(pop_back(seq, &i));
    assert(i == 30);
    dump(seq);

    assert(pop_back(seq, &i));
    assert(i==100);
    dump(seq);

    push_back(&seq, 4);
    push_back(&seq, 4023);
    dump(seq);

    assert(get(seq, 4) == 0);
    push_back(&seq, 300);
    push_back(&seq, 600);
    assert(get(seq, 4) == 600);
    dump(seq);

    return 0;
}


