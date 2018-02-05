#include "sort_common.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 20
int g_arr[MAX] = {
    3,-4,8,-10,-15,20,-9,-1,0,-7,
    15,6,-2,-7,19,25,30,12,2,1,
};

void _quick_sort_private(int *arr, int length) {
    int t=0, k=arr[t], i=0, j=length-1;
    if(length < 1 || !arr) return ;

    while(i < j) {
        for(; i<t && i< j; ++i) {
            if(arr[i] > k)  {
                arr[t]=arr[i];
                t=i;
                break;
            }
        }
        for(;j>t && i < j;--j) {
            if(arr[j] < k) {
                arr[t]=arr[j];
                t=j;
                break;
            }
        }
    }

    arr[t]=k;
    _quick_sort_private(arr,t-1);
    _quick_sort_private(arr+(t+1), length-(t+1));
}

void quick_sort(int *arr, int length) {
    _quick_sort_private(arr, length);
}

void show(int *arr, int length) {
    int i;
    if(length <=0 || !arr) return ;
    for(i=0; i<length;++i) {
        printf("%d,",arr[i]);
    }
    printf("\n");
}

void init(int *arr, int length){
    int l=length<MAX?length:MAX, i;
    if(!arr || length < 1) return ;

    for(i=0; i<l;++i) {
        arr[i]=g_arr[i];
    }
}

void init_random(int *arr, int length) {
    int i;
    srand(time(NULL));
    if(!arr || length < 1) return ;
    for(i=0; i<length; ++i) {
        arr[i]=rand();
    }
}
void init_left_sorted(int *arr, int length) {
    int n;
    if(!arr || length < 1) return ;
    init(arr, length);
    n=length/2;
    quick_sort(arr, n);
}

void init_right_sorted(int *arr, int length){
    int n;
    if(!arr || length < 1) return ;
    init(arr, length);
    n=length/2;
    quick_sort(arr+length-n, n);
}


