#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

#define QuickSortCutOff 20
#define N 300

void swap(int *a , int *b) {
    if(!a || !b) return ;
    int t { *a};
    *a = *b;
    *b = t;
}

namespace InsertSort {

    void insertSort(int *a, int *b) {
        if(!a || !b || a >= b) return ;
        int *i = a, *j = b, *k;

        for(++i; i <= j; ++i) {
            int c = *i;
            int *d = i;
            for(k = i-1; k >= a; --k) {
                if(*k > c) {
                    *(k+1) = *k;
                    d = k;
                } else break;
            }
            *d = c;
        }
    }

}

namespace QuickSort {
    int* median(int *a, int *b) {
        if(!a || !b) return nullptr;
        int *c = a+ (b-a)/2;
        int x = *a, z= *b, y = *c;
        if(x > y) {
            swap(a, c);
        }
        if(x > z) {
            swap(a, b);
        }
        if(y > z) {
            swap(c, b);
        }

        //将中枢元素交换到最后的位置
        swap(c, b);
        return b;
    }

    void quickSortPrivate(int *a, int *b) {
        if(!a || !b || a >= b) return;
        if(a + QuickSortCutOff < b) {
            int *pivot = median(a, b);
            int *i, *j;
            int k = *pivot;
            for(i = a, j = b-1; ; ) {
                for(; !(*i > k); ++i) {}
                for(; !(*j < k); --j) {}

                if(i < j)
                    swap(i, j);
                else
                    break;
            }
            swap(i, pivot);

            quickSortPrivate(a, i-1);
            quickSortPrivate(i+1, b);
        } else {
            InsertSort::insertSort(a,b);
        }
    }

    void quickSort(int *d,  int len) {
        if(!d || len < 1) return ;
        quickSortPrivate(d, d+len-1);
    }

}

void show(int *arr) {
    copy(arr, arr + N, ostream_iterator<int>(cout, " "));
    cout<<endl;
}

int main()
{
    int arr[N];
    for(int i=0; i<N; ++i) arr[i] = i+1;
    random_shuffle(arr, arr + N);
    show(arr);

    QuickSort::quickSort(arr, N);
    show(arr);

    return 0;
}
