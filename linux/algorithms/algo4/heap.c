/*!
 * 二叉堆 (d叉堆), 完全二叉树
 * 堆的性质
 * 1.父节点一定大于(大根堆)，或小于(小根堆)孩子节点
 * 2.上滤 percolateUp, 增加一个数据到堆中,仅和根元素比较
 * 3.下滤 percolateDown,从堆中删除堆顶，需要比较左右孩子
 * 4.父子之间存在如下关系，从0开始计数，如果父节点为i, 子节点2*i+1, 2*i+2, 
 * 4-1.数据结构算法与分析上建议从1开始计数，这样的话，正好可以[1,N],子节点2*i, 2*i+1
 * 5.如果子节点是i(从0开始), 父节点为(i-1)/2 (向下取整)
 * 5-1.如果子节点是i(从1开始),父节点i/2(向下取整)
 */

#include "common.h"
#define RECURSIVE 

/*!
 * index表示子节点索引*/
void
percolateUp(int *arr, int index, int size) {
    if(!arr || index < 1 || index > size) return; //基础判断条件
    int p = index/2, tmp;
    if(p < 1) return ;//递归基

    //仔细注意这里递归和非递归的写法是不同的，递归的话必须要交换数据
    //非递归的时候可以采用移动方法来填充元素
    if(arr[p] > arr[index]) { //元素移动,快速排序和插入排序中也有使用
        tmp = arr[p];
        arr[p] = arr[index];
        arr[index] = tmp;
        return percolateUp(arr, p, size);
    }
}

/*!
 * index表示子节点
 */
void
percolateUpNR(int *arr, int index, int size) {
    if(!arr || index < 1 || index > size) return ;
    int p;
    int v = arr[index];
    for(p=index/2; p >= 1; p = index/2) {
        //在移动赋值进行比较的时候，要使用备份的数据
        if(arr[p] > v) {
            arr[index] = arr[p];
            index = p;
        } else break; //条件已经成立,可以停下来了
    }

    arr[index] = v;
}

/*!
 * index表示父节点
 */
void
percolateDown(int *arr, int index, int size) {
    if(!arr || index < 1 || index > size) return ;
    int l = 2*index, r = 2*index+1,tmp;
    if(r <= size && arr[r] < arr[l]) l = r;
    //bugs-4 缺少对l索引的限制条件
    if(l <= size && arr[index] > arr[l]) {
        tmp = arr[index];
        arr[index] = arr[l];
        arr[l] = tmp;
        return percolateDown(arr, l, size);
    }
}

/*!
 * index表示父节点
 */
void
percolateDownNR(int *arr, int index, int size) {
    if(!arr || index < 1 || index > size) return ;
    int l, r;
    int v = arr[index];
    while(true) {
        l = 2 *index ; r = 2*index+1;
        if(r <= size  && arr[r] < arr[l]) l = r;
        if(l > size) break;

        //bugs-1,在使用移动赋值进行比较的时候，要使用数值
        if(v  > arr[l]) {
            arr[index] = arr[l];
            index = l;
        } else break; //条件已经成立，不需要再折腾
    }
    //bugs-2 赋值的方向不正确，将备份数据进行恢复
    arr[index] = v;
}

#if !defined(RECURSIVE)
#define PD percolateDownNR
#define PU percolateUpNR
#else
#define PD percolateDown
#define PU percolateUp
#endif

void
show(int *a, int n) {
    int i;
    printf("Elements:\n");
    for(i=1; i<=n; ++i) printf("%d ", a[i]);
    printf("\n");

}

int
main(int argc, char *argv[]) {
    int n;
    printf("Please input N numbers:");
    fflush(stdout);
    scanf("%d", &n);
    if(n < 1) {
        return 1;
    }

    int i, *arr;
    arr = (int*)malloc(sizeof(int) * (n+1)); //预留一个哨兵的位置
    arr[0]=-1;//0作为哨兵
    for(i=1; i<=n; ++i) {
        scanf("%d", &arr[i]);
    }

    show(arr, n);
    //建小根堆，自下而上进行下滤
    for(i = n/2; i> 0; --i) {
        PD(arr, i, n);
    }

    //出堆测试
    int sz = n, tmp;
    for(; sz >= 1; ) {
        printf("(1).[%d],Top of heap:%d\n", n-sz+1,arr[1]);
        tmp = arr[1];
        arr[1] = arr[sz];
        arr[sz] = tmp;
        sz--;
        PD(arr, 1, sz);
    }

    show(arr, n);
    //入堆测试
    for(sz = 1; sz <= n; ) {
        printf("(2).[%d],Top of heap:%d\n", sz,arr[1]);
        ++sz;
        PU(arr, sz, sz);
    }

    free(arr);
    return 0;
}

