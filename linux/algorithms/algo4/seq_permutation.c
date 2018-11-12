/*!
 * 序列排列
 * 实现STL中的permutation算法
 */

#include <stdio.h>
#include <stdlib.h>

#define LARGEN 5000

void 
sort(int *nums, int count) {
    if(count < 1) return ;
    int i = count/2;
    int v = nums[i];
    int j = 0, k = count-1, t;

    for(; j < k; ) {
        for(; j < i; ++j) {
            if(nums[j] > v) {
                nums[i] = nums[j];
                i = j;
                break;
            }
        }

        for(; i < k; --k) {
            if(nums[k] < v) {
                nums[i] = nums[k];
                i = k;
                break;
            }
        }
    }

    nums[i] = v;
    sort(nums, i);
    sort(nums+i+1, count-(i+1)-1);
}

void
swap(int *i, int *j) {
    if(!i || !j) return ;
    int t = *i;
    *i = *j;
    *j = t;
}

//含元素j
void
reverse(int *i, int *j) {
    for(j; i<j; ++i, --j) {
        swap(i, j);
    }
}

int
next_permutation(int *nums, int count) {
    if(count < 1) return 0;
    if(count == 1) return 0;

    int *i, *j, *k;
    int *last , *first;

    first = nums;
    i = last = nums + count -1;

    while(1) {
        /* i和j是邻居关心 */
        j = i;
        i--;
        
        if(*i < *j) {
            k = last;
            for(; !(*i < *(k)); --k) {}

            /*!找到第一个i < k的位置 */
            swap(i, k);
            reverse(j, last);

            //getchar();
            return 1; //仍然可以继续排列
        }

        if(i == first) {
            reverse(i, last);
            return 0; //排列终止
        }
    }

    return 0;
}

void
show(int *nums, int count) {
    for(int i=0; i<count; ++i) printf("%d ", nums[i]);
    printf("\n");
}

void
testSort() {
    int nums[LARGEN];
    int count = sizeof(nums) / sizeof(int);
    for(int i=LARGEN-1; i>=0; --i) nums[i] = LARGEN-i;
    sort(nums, count);
    show(nums, count);
}

int
main(int argc, char *argv[]) {
    //testSort();

    int n = 4, type;
    do {
        scanf("%d", &n);
        if(n < 1 || n>100) break;
        int *arr = (int*)malloc(sizeof(int) * n);

        /*! 第一个排列必须是升序排列 */
        for(int i=0; i<n; ++i) arr[i] = i+1;

        show(arr, n);
        type = 1;
        while(next_permutation(arr, n)) {
            show(arr, n);
            type++;
        }
        printf("types of all:%d\n", type);

        free(arr);
        printf("\n");
        fflush(stdout);
    } while(1); 
    return 0;
}



