/*!
 * optimize bubble sort
 * l->r 从左到右
 * r->l 从右到左
 * 单从趟数(i)考虑，直接j从右向左
 * 通过测试，可以得出j值的比较，从右往左的效率是最高的
 * 双向的话，趟数绝对是最少的
 */
#include "sort_common.h"

#define ORDER <
/*!
 * i l->r
 * j l->r
 */
void bubble_sort1(int *a, int len) {
    int i,j,t,k,s=0, sa=0;
    i=len-1;
    while(true){
        s++;
        k=len-1;
        for(j=0; j<i;++j) {
            sa++;
            if(a[j] ORDER a[j+1]) {
                t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
                k=j;
            }
        }
        if(k==len-1) break;
        i=k;
    }
    printf("bubble_sort1: step=%d, step_all=%d.\n", s, sa);
}

/*!
 * i l->r
 * j r->l
 */
void bubble_sort2(int *a, int len) {
    int i,j,k,t,s=0,sa=0;
    i=0;
    while(true) {
        k=0;
        s++;
        for(j=len-1; j>i;--j) {
            sa++;
            if(a[j-1] ORDER a[j]) {
                t=a[j];
                a[j]=a[j-1];
                a[j-1]=t;
                k=j;
            }
        }
        if(k==0) break;
        i=k;
    }
    printf("bubble_sort2: step=%d, step_all=%d.\n",s,sa);
}

void bubble_sort3(int *arr, int len){
    int j,k,t,s=0,sa=0;
    int i1=len-1, i2=0;
    if(!arr || len<1) return ;

    while(true) {
        s++;
        k=len-1;
        for(j=0; j<i1;++j){
            sa++;
            if(arr[j] ORDER arr[j+1]) {
                t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
                k=j;
            }
        }
        if(k==len-1) break;
        i1=k;

        k=0;
        for(j=len-1; j>i2;--j) {
            sa++;
            if(arr[j-1] ORDER arr[j]) {
                t=arr[j-1];
                arr[j-1]=arr[j];
                arr[j]=t;
                k=j;
            }
        }
        if(k==0) break;
        i2=k;
    }
    printf("bubble_sort3: step=%d, step_all=%d.\n",s,sa);
}

#define N 20

int main() {
    int arr[N];
    init(arr, N);
    show(arr, N);

    bubble_sort1(arr, N);
    show(arr, N);

    init_left_sorted(arr, N);
    bubble_sort1(arr, N);
    show(arr, N);

    init_right_sorted(arr,N);
    bubble_sort1(arr, N);
    show(arr, N);

    printf("================================\n");
    init(arr,N);
    bubble_sort2(arr, N);
    show(arr, N);

    init_left_sorted(arr, N);
    bubble_sort2(arr, N);
    show(arr, N);

    init_right_sorted(arr,N);
    bubble_sort2(arr, N);
    show(arr, N);

    printf("================================\n");
    init(arr,N);
    bubble_sort3(arr, N);
    show(arr, N);

    init_left_sorted(arr, N);
    bubble_sort3(arr, N);
    show(arr, N);

    init_right_sorted(arr,N);
    bubble_sort3(arr, N);
    show(arr, N);

    return 0;
}

