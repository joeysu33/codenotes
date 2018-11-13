/*!
  水仙花数，输出100~999中所有的水仙花数
  若ABC满足ABC = A³ + B³ + C³,
  则ABC是水仙花数

  P1:变量赋值要注意，直接搞成死循环了
  P2:要正确书写题意, A³是A*A*A
*/

#include <iostream>

using namespace std;

int main()
{
    int s = 0;
    for(int j=100, i,a, b, c; j<1000; ++j) {
        i = j;
        c = i % 10; i /= 10;
        b = i % 10; i /= 10;
        a = i % 10;
        s = a*a*a + b*b*b + c*c*c;
        if(s == j) printf("%d ", j);
    }

    return 0;
}
