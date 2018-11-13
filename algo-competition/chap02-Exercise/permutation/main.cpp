/*!
  用1,2...9组成3个3位数，abc, def和ghi，每个数字恰好只用一次，
  要求abc:def:ghi = 1:2:3
  1.排列所有9!，并校验
  2.回溯法求解，通过剪枝排除大部分
*/
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

#define N 9

namespace {
void swap(int *i, int *j) {
    if(!i || !j) return ;
    int t{*i};
    *i = *j;
    *j = t;
}

void reverse(int *i, int *j) {
    if(!i || !j) return ;
    for(; i < j;++i, --j) {
        swap(i, j);
    }
}

bool nextPermutation(int *num, int count) {
    if(!num || count < 1) return false;
    int *a, *b, *c, *last, *first;
    first = num;
    last = num+count-1;
    a = last;

    while(true) {
        b = a;
        //a始终在b的左边
        a--;

        //满足升序序列
        if(*a < *b) {
            c = last;
            //c至多走到b的位置，c肯定存在因为b<=c
            for(; !(*a < *c); --c) {}
            swap(a, c);
            reverse(b, last);
            return true;
        }

        if(a == first) {
            reverse(first, last);
            return false;
        }
    }

    return false;
}

int toInt(int *num) {
    return num[0]*100 + num[1]*10 + num[2];
}
}

int main()
{
    int num[N], a, b, c, cnt;
    for(int i=0; i<N; ++i) num[i] = i+1;

    //copy(num, num+N, ostream_iterator<int>(cout, " "));
    //cout<<endl;
    cnt = 0;
    do {
        cnt++;
        a = toInt(num);
        b = toInt(num+3);
        c = toInt(num+6);

        if(b % a != 0 || c % a != 0)
            continue; //doWhile中的continue表示直接跳到while判断，不继续执行
        if(b / a == 2 && c / a == 3) { printf("%d %d %d\n", a, b, c); }
    } while(nextPermutation(num, N));

    return 0;
}
