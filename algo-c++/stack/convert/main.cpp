/*!
  进制转换问题，将10进制转换为任意进制
  */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

static const char ctb[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F',
};

string convert(int n, int base) {
    if(n < 1) return string();
    if(base < 1 || base > 16) return string();
    char buf[1000];
    int i=0;
    while(n > 0) {
        buf[i++] = ctb[n % base];
        n /= base;
    }
    buf[i]=0;
    for(int a=0, b=i-1; a < b; ++a, --b) {
        std::swap(buf[a], buf[b]);
    }
    return string(buf);
}

int main()
{
    cout<<convert(96, 10)<<endl;
    cout<<convert(96, 5)<<endl;
    cout<<convert(96, 16)<<endl;
    return 0;
}
