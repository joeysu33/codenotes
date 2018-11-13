/*!
  输出所有形如aabb的4位完全平方数
  既前两位和后两位相等
*/
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include "utility/output.h"

using namespace std;

void
case1() {
int a, b;
for(int i=1; i<=9; ++i)
    for(int j=0; j<=9; ++j) {
        a = i*1100 + j*11;
        b = (int)floor(sqrt(a) + 0.5);
        if(a == b*b) printf("%d", a);
    }
}

void
case2() {
    char buf[8];
    for(int i=1; i<=9; ++i)
        for(int j=0; j<=9; ++j) {
            int a = i+'0', b = j + '0';
            char *cp;
            sprintf(buf,"%c%c%c%c", a,a, b, b);
            int c = strtol(buf, &cp, 0);
            int d = (int)floor(sqrt(c) + 0.5);
            if(c == d*d ) printf("%d", c);
        }
}


int main()
{
    case1();
    Output::newSplitLine();
    case2();
    return 0;
}
