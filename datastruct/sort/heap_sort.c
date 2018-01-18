/*!
 * 堆排序
 * 堆的数据结构分为大根堆和小根堆（大根堆中堆顶的值最大，小根堆中堆顶的元素最小)
 * 堆是一个完全二叉树，采用数组进行存储，满足的条件是
 * 大根堆：父节点大于所有的子节点（大于子节点中最大的）
 * 小根堆：父节点小于所有的子节点（小于子节点中最小的）
 * 要点: 1.堆排序的原理（采用完全二叉树，使用数组进行存储）
 *       可以进行堆排序的必须是能随机访问的
 *       2.topK问题，例如
 *       从100万个数据中找出第10大(或小)的数据
 *       从100万个数据中找出10个最大(或小)的数据
 *       3.priority queue
 *
 * 完全二叉树的性质(索引从0开始)
 * 节点的索引是i，
 * 1.左子节点一定是2*i+1
 * 2.右子节点是2*i+2
 * 3.父节点是(i-1)/2
 */

#include "sort_common.h"

/*!
 * 构建一个小根堆
 * arr 数组
 * i   非叶子节点（从非叶子节点开始从上至下递归处理)
 * length 数组的长度
*/
void make_heap(int *arr, int i, int length) {
    int j=0, t=0;
    if(!arr || i<0 || i>= length || length < 2) return ;
    j=2*i+1;
    /*!检测j是否越界(因为没有这句，导致了很严重的栈溢出*/
    if(j >= length) return ;
    if((j+1) < length && arr[j+1] < arr[j]) ++j;
    if(arr[i] > arr[j]) {
        t=arr[i];
        arr[i]=arr[j];
        arr[j]=t;
        /*!递归处理子节点*/
        make_heap(arr, j, length);
    }
}

void heap_sort() {
    int i=0,j=0,n=0, arr[15] = {3, 7, -10, 8, 1, 
                   0, 6, 7, 100,  20, 
                   70, -9, -6, -3, 666};
    /*!
     * 将原始数据构建成堆，所有非叶子节点均满足堆的性质
     */
    //获取最后一个非叶子节点 2*n+1 = 14,n>=2
    n=sizeof(arr) / sizeof(arr[0]);
    i=(n-2)/2;

    printf("before heap sort\n");
    show(arr, n);
    for(; i>=0; --i) {
        make_heap(arr, i, n);
    }

    /*!
     * 将堆顶的元素逐个弹出，缩小堆规模
     * 降序排列
     * 这里特别需要注意的是i>=1,如果不取等的话，会有问题
     * 必须要>=1，否则少一次退堆顶
     */
    for(i=n-1; i>=1;--i) {
        j=arr[i];
        arr[i] = arr[0];
        arr[0] = j;
        make_heap(arr, 0, i);
    }

    printf("after heap sort\n");
    show(arr, n);
    for(i=0; i<n-2;++i) {
        if(arr[i] < arr[i+1]) {
            printf("heap_sort errors.\n");
            assert(false);
        }
    }
}

void make_heap_test() {
    /*! 
     * arr已经是一个堆结构，从堆从弹出堆顶
     * 再次构建堆
     * */
    int arr[10] = {0,2,1,4,3,9,5,8,6,7};
    arr[0] = arr[9];
    make_heap(arr, 0, 9);
    show(arr, 9);
}

int main() {
    make_heap_test();
    heap_sort();
    return 0;
}

