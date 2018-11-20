/*!
  周期性子串
  输入一个不超过80的字符串，输出其最小周期，例如
  abcabcabcabc，最小周期为3，（周期也是6和12)
*/
#include <iostream>

using namespace std;

#define MAX_LEN 100

int minPeriod(const char * s) {
    if(!s) return 0;

    /*!
      周期性子串，满足两个条件
      1.能被整除
      2.对应的字符相同
    */
    bool isOk;

    int slen=strlen(s);
    for(int j=1; j < slen; ++j) {
        if(slen % j != 0) continue;
        isOk = true;
        for(int m=0; m < j; ++m) {
            for(int n=m+j; n < slen; n+=j) {
                if(s[m] != s[n]) { isOk = false; break;}
            }
            if(!isOk) break;
        }

        if(isOk) return j;
    }

    return slen;
}

int main()
{
    char str[MAX_LEN];
    if(scanf("%s", str) != 1) return 1;
    printf("%d",minPeriod(str));

    return 0;
}
