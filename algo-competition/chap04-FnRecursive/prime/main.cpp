/*!
  判断一个数字是否是素数
  素数的条件，只能被1或其本身整除
  由于除数的对称关系，所以只需要满足
  2 ~ floor(sqrt(x)+0.5),之间找不到除数即可
*/
#include <iostream>
#include <cstdint>
#include <cmath>
#include <climits>

using namespace std;

/*!
  1.i*i很容易溢出,int的最大值是21*10^9左右，所以很不安全，
  而且一旦溢出，i*i < 0,导致死循环
 */
bool isPrime1(int x) {
    if(x <= 2) return false;
    //i*i存在溢出风险,为了避免溢出也可以将i=2, uint_t i=2
    for(int i=2; i*i < x; ++i) {
        if(x % i == 0)
            return false;
    }
    return true;
}

/*!
  这个方案比上述方案要优秀很多，x的取值可以更大,不会溢出
 */
bool isPrime2(int x) {
    if(x <= 2) return false;
    int n = floor(sqrt(x) + 0.5);
    for(int i=2; i<n; ++i) {
        if(x % i == 0) return false;
    }
    return true;
}

/*!
  扩大描述范围
 */
bool isPrime3(uint64_t x) {
    if(x <= 2) return false;
    uint64_t n = (uint64_t)floor(sqrt((long double)x) + 0.5);
    for(uint64_t i=2; i<n; ++i) {
        if(x % i == 0)
            return false;
    }
    return true;
}

int main()
{
    isPrime1(INT_MAX); //输出的结果是错误的
    isPrime2(INT_MAX); //INT_MAX就是一个素数
    isPrime3(UINT64_MAX);
    return 0;
}
