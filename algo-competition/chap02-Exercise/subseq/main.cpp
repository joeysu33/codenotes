/*!
 求子序列的和
 n<m<10^6 输出1/n^2 + 1/(n-1)^2 +...1/m^2,保留5位小数
*/
#include <iostream>

using namespace std;
#define MAX_DATA 1000

struct InputData { int n, m;};

int main()
{
    InputData id[MAX_DATA];
    int i, cnt;
    for(i=0; i<MAX_DATA;) {
        cnt = scanf("%d%d", &id[i].n, &id[i].m);
        if(cnt == 2 && id[i].n==0 && id[i].m==0) break;
        if(cnt != 2 || id[i].n >= id[i].m || id[i].n < 1) return 1;
        ++i;
    }

    double d;
    for(int j=0; j<i; ++j) {
        d = 0;
        for(int k=id[j].n; k<=id[j].m; ++k) {
            d += 1.0/k/k;
        }
        printf("Case %d:%.5lf\n", j+1, d);
    }

    return 0;
}
