/*!
  计算阶乘之和
  S = 1! + 2! + 3! + .... N!
  计算S结果的最后6位,且N < 10^6

  注意点
  1。最后6位 S %= 1000000
  2。S溢出的情况
  3。计算时间 10^6时间很慢
*/

#include <iostream>
#include <cstdio>

using namespace std;

/*! 返回结果的最后6位 1000000*/
static const int MOD = 1000000;

int main()
{
    int n;
    scanf("%d", &n);
    int s = 0, fab = 0;
    if(n > 25) n=25; //因为25!的尾数正好存在6个0，所以后面的数据取余都是它自己
    for(int i=1; i<=n; ++i) {
        fab = 1;
        for(int j=1; j<=i; ++j) {
            fab *= j;
            fab %= MOD;
        }
        s += fab;
        s %= MOD;
    }

    printf("%d",s);
    return 0;
}
