#include "sort_common.h"

#define NUM 10

/*!
 * -> 从左到右扫描
 */
void bubble_sort1(int *arr, int length) {
    int i,j,t;
    for(i=0; i<length-1; ++i) {
        for(j=0;j<length-1-i;j++) {
            if(arr[j] > arr[j+1]) {
                t=arr[j]; 
                arr[j]=arr[j+1];
                arr[j+1]=t;
            }
        }
    }
}

/*!
 * 从右到左
 */
void bubble_sort2(int *arr, int length) {
}

/*!
 * 双向
 */
void bubble_sort3(int *arr, int length) {
}

void bubble_sort_optimized1(int *arr, int length) {
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
		
	}
    fprintf(stdout, "bubble_sort_optimized2::step=%d,stepAll=%d\n",step,stepAll);
}

int main() {
    int arr[NUM] = {999,10, 3, 4, 8, -1, -5, 0, 20, 34 };
    show(arr,NUM);
    bubble_sort_optimized2(arr,NUM);
    show(arr,NUM);

    return 0;
}

