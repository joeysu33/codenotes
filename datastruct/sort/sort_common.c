#include "sort_common.h"

void show(int *arr, int length) {
    int i;
    if(length <=0 || !arr) return ;
    for(i=0; i<length;++i) {
        printf("%d,",arr[i]);
    }
    printf("\n");
}
