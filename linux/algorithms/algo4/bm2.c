/*!bm算法*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NSYM 256

int*
makeKmpNext(const char *p) {
    int *next;
    int i, j, k;
    i=0;
    j=-1;
    k = strlen(p);
    next = (int*)malloc(sizeof(int) * k);
    next[i] = j; /*! j描述的是后缀与前缀匹配的位置*/
    while(i < k-1) {
        if(j < 0 || p[i] == p[j]) {
            i++;
            j++;
            next[i] = p[i]==p[j] ? next[j] : j;
        } else {
            j = next[j];
        }
    }

    return next;
}

int*
makeSS2(const char *p) {
    int i,j,k,q;
    int *ss ;
    k = strlen(p);
    ss = (int*)malloc(sizeof(int) * k);
    
    for(i=k-2; i>=0; --i) {
        q = i;
        while(q >= 0 && p[q] == p[k-1-i+q]) {
            --q;
        }
        ss[i] = i-q;
    }

    return ss;
}

int*
makeSS(const char *p) {
    int *ss;
    int i,j, k;
    if(!p) return NULL;
    j = strlen(p);
    ss = (int*)malloc(sizeof(int) * j);

    return ss;
}

int*
makeGS(const char *p) {
    int i, j,k;
    int *gs;
    k = strlen(p);
    gs = (int*)malloc(sizeof(int) * k);
    return gs;
}

int*
makeBC(const char *p) {
    int *bc = (int*)malloc(sizeof(int) * NSYM);
    int i, j, k;
    k = strlen(p);
    for(i=0; i<NSYM; ++i) {
        bc[i] = k;
    }

    return bc;
}



int 
main(int argc, char *argv[]) {
    return 0;
}

