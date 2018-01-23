#include "sort_common.h"

#define NUM 10

/*!
 * -> 从左到右扫描
 */
void bubble_sort1(int *arr, int length) {
    int i,j,t;
    bool swaped;
    int m,n;
    m=0;n=0;
    for(i=0; i<length-1; ++i) {
        swaped=false;
        m++;
        for(j=0;j<length-1-i;j++) {
            n++;
            if(arr[j] > arr[j+1]) {
                t=arr[j]; 
                arr[j]=arr[j+1];
                arr[j+1]=t;
                swaped=true;
            }
        }
        if(!swaped) break;
    }
    fprintf(stdout,"bubble_sort1 step=%d allstep=%d.\n",m,n);
}

/*!
 * 从右到左
 */
void bubble_sort2(int *arr, int length) {
    int i,j,t;
    bool swaped;
    int m,n;
    m=0;n=0;
    for(i=0; i<length-1;++i) {
        swaped=false;
        m++;
        for(j=length-1; j>i;--j) {
            n++;
            if(arr[j] < arr[j-1]) {
                t=arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=t;
                swaped=true;
            }
        }
        if(!swaped) break;
    }
    fprintf(stdout,"bubble_sort2 step=%d allstep=%d.\n",m,n);
}

/*!
 * 双向
 */
void bubble_sort3(int *arr, int length) {
}

void bubble_sort_optimized1(int *arr, int length) {
    int i,j,k,t, m,n;
    bool swaped;
    m=0;n=0;t=0;
    for(i=0; i<length-1; ++i) {
        m++;
        swaped=false;
        for(j=0; j<length-1-i; ++j) {
            n++;
            if(arr[j] > arr[j+1]) {
                t=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=t;
                swaped=true;
            }
        }

        for(k=length-1; k>i;--k) {
            n++;
            if(arr[k] < arr[k-1]) {
                t=arr[k];
                arr[k]=arr[k-1];
                arr[k-1]=t;
                swaped=true;
            }
        }
        if(!swaped) break;
        show(arr,length);
    }
    fprintf(stdout,"optimized1 step=%d allstep=%d.\n",m,n);
}

void bubble_sort_optimized2(int a[], int size)
{
	int lastSwapPos = 0,lastSwapPosTemp = 0, stepAll=0, step=0;
	for (int i = 0; i < size - 1; i++)
	{
		lastSwapPos = lastSwapPosTemp;
        step++;
		for (int j = size - 1; j >lastSwapPos; j--)
		{
            stepAll++;
			if (a[j - 1] > a[j])
			{
				int temp = a[j - 1];
				a[j - 1] = a[j];
				a[j] = temp;

				lastSwapPosTemp = j;
			}
		}
		if (lastSwapPos == lastSwapPosTemp)
			break;
        show(a,size);
		
	}
    fprintf(stdout, "bubble_sort_optimized2::step=%d,stepAll=%d\n",step,stepAll);
}

void test(void (*func) (int *, int ), int *a) {
    int arr[NUM];
    memcpy(arr,a, NUM*sizeof(int));
    func(arr,NUM);
    show(arr,NUM);
    printf("-------------------------------\n");
}

int main() {
    int arr[NUM] = {3,2, 1, -14, -8, 0, 5, 10, 20, 34 };
    printf("origin data:\n");
    show(arr,NUM);

    test(bubble_sort1, arr);
    test(bubble_sort2, arr);
    test(bubble_sort3, arr);
    test(bubble_sort_optimized1, arr);
    test(bubble_sort_optimized2, arr);
    /*
    bubble_sort_optimized2(arr,NUM);
    show(arr,NUM);

    bubble_sort_optimized1(arr2,NUM);
    show(arr2,NUM);
    */

    return 0;
}

