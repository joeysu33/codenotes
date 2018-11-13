/*!
绘制倒三角 */
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int n, cnt;
    do {
        cnt = scanf("%d", &n);
        if(cnt != 1 || n < 1 || n >20) break;
        for(int i=0; i<n; ++i) {
            for(int j=0; j<i; ++j)
                printf(" ");
            for(int k=0; k<2*(n-i)-1; ++k)
                printf("#");
            printf("\n");
            fflush(stdout);
        }
    } while(true);
    return 0;
}
