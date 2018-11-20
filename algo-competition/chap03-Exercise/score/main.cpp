/*!
  求得分,长度为1-80,每个O的得分是连续出现的个数，X的得分是0
  例如OOXXOXXXOOOO = 1+2+0+0+1+0+0+0+1+2+3+4
*/
#include <iostream>

using namespace std;

#define MAX_LEN 100

int score(const char *s) {
    if(!s) return 0;
    int sco;
    int sa[MAX_LEN];
    memset(sa, 0, sizeof(sa));
    bool isX = false;
    int i,j;

    for(i=0; *s; ++s,++i) {
        isX = *s == 'X';
        if(i==0) { isX ? (sa[i] = 0) : (sa[i] = 1); continue;}

        if(isX) sa[i]=0;
        else sa[i] = sa[i-1]+1;
    }

    sco=0;
    for(j=0; j<i; ++j) sco += sa[j];
    return sco;
}

int main()
{
    char str[MAX_LEN];
    if(scanf("%s", str) != 1) return 0;
    printf("%d", score(str));
    return 0;
}
