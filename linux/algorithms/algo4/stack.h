/*!
 * stack 基于vector的实现，和基于linkedlist的实现
 * pre-defined element type
 * #define ETYPE int
 */

#if !defined(_STACK_INCLUDED_H_)
#define _STACK_INCLUDED_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _Stack {
    ETYPE *m_d;
    int m_top;
    int m_cap;
} Stack;

int
sizeS(Stack *s) ;
int
fullS(Stack *s) ;
int
emptyS(Stack *s);

void
clearS(Stack *s) {
    s->m_d = NULL;
    s->m_top = -1;
    s->m_cap = 0;
}

Stack
makeS(int stackSize) {
    Stack s;
    clearS(&s);
    if(stackSize < 1) return s;

    s.m_d = (ETYPE *)malloc(sizeof(ETYPE) * stackSize);
    s.m_top = -1;
    s.m_cap = stackSize;
    return s;
}

void
freeS(Stack *s) {
    if(!s) return ;
    free(s->m_d);
    clearS(s);
}

void
pushS(Stack *s, ETYPE val) {
    if(fullS(s)) return ;
    s->m_d[++s->m_top] = val;
}

ETYPE
popS(Stack *s) {
    if(emptyS(s)) return (ETYPE)-1;
    return s->m_d[s->m_top--];
}

ETYPE
topS(Stack *s) {
    if(emptyS(s)) return (ETYPE)-1;
    return s->m_d[s->m_top];
}

int
emptyS(Stack *s) {
    if(!s) return 1;
    return (sizeS(s) == 0) ? 1 : 0;
}

int
fullS(Stack *s) {
    if(!s) return 1;
    return (sizeS(s) == s->m_cap) ? 1 : 0;
}

int
sizeS(Stack *s) {
    if(!s) return 0;
    if(s->m_top < 0) return 0;
    return s->m_top+1;
}

#endif //_STACK_INCLUDED_H_

