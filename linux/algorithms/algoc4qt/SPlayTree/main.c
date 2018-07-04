#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "splay.h"

#define DATASIZE 10

void
random_shuffle(int *d, int cnt) {
    int i, j, k, t;
    for(i=0; i <cnt * 4; ++i) {
        j=rand() % cnt;
        k= rand() % cnt;
        if(j == k) continue;

        t = d[j];
        d[j] = d[k];
        d[k] = t;
    }
}

void
showTree(const int mode, SplayTree t) {
    if(!t) return ;
    if(mode == 0)
        printf("%d ", t->Element);
    showTree(mode, t->Left);
    if(mode == 1)
        printf("%d ", t->Element);
    showTree(mode, t->Right);
    if(mode == 2)
        printf("%d ", t->Element);
}

void
destroyTree(SplayTree t) {
    if(!t) return ;
    destroyTree(t->Left);
    destroyTree(t->Right);
    free(t);
}

void
show(int mode, SplayTree t, const char *s) {
    printf("%s:", s);
    showTree(mode, t);
    printf("\n");
}

int main()
{
    int d[DATASIZE];
    char buf[64];
    int i, j;

    SplayTree t;
    srand(time(NULL));
    for(i = 0; i<DATASIZE; ++i) d[i] = i+1;
    random_shuffle(d, DATASIZE);

    t = Initialize();
    for(i=0; i<DATASIZE; ++i) {
        t = Insert(d[i], t);
        snprintf(buf, sizeof(buf), "insert %d, SplayTree:", d[i]);
        show(1, t, buf);
        assert(t->Element == d[i]);
    }

    return 0;
}
