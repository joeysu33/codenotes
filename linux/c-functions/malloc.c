#include <malloc.h>
#include <stdio.h>
#include <unistd.h> //brk sbrk

#define N 10

void show_program_break() {
    printf("brk=%p\n",sbrk(0));
}

void show_malloc_st(char *p, char* name, int n) {
        int i;
        printf("%s malloc(0x%x) %s=%p \n",name,n, name,p);
        for(i=0; i<8; ++i) {
            printf("0x%x ",*(p-8+i));
        }
        printf("\n");
}

int main(int argc, char *argv[]) {
    char *pa[N] = {0};
    char *p ;
    int i,n;
    show_program_break();
    p = (char*)malloc(0);
    if(!p) {
        printf("malloc(0) p==NULL\n");
    } else {
        show_malloc_st(p,"p",0);
    }
    show_program_break();

    n=0x11111111;
    pa[0]=(char*)malloc(n);
    show_malloc_st(pa[0], "pa[0]",n);
    show_program_break();

    pa[1]=(char*)malloc(8);
    show_malloc_st(pa[1], "pa[1]",8);

    pa[2]=(char*)malloc(16);
    show_malloc_st(pa[2], "pa[2]",16);

    show_program_break();
    for(i=N-1; i>=0; --i) free(pa[i]);
    show_program_break();
    free(p);
    return 0;
}
