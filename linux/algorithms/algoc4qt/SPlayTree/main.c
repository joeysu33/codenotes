#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <assert.h>
#include "splay.h"

#define DATASIZE 10

int main()
{
    int d[DATASIZE];
    int id[DATASIZE] = {6, 5, 4, 3, 1, 7, 9, 2, 8, 10};
    char buf[64];
    int i, j;

    SplayTree t;
    srand(time(NULL));
    for(i = 0; i<DATASIZE; ++i) d[i] = i+1;
    random_shuffle(d, DATASIZE);

    memcpy(d, id, sizeof(d));
    t = Initialize();
    for(i=0; i<DATASIZE; ++i) {
        t = Insert(d[i], t);
        snprintf(buf, sizeof(buf), "insert %d, SplayTree:", d[i]);
        show(1, t, buf);
        assert(t->Element == d[i]);
    }

    return 0;
}
