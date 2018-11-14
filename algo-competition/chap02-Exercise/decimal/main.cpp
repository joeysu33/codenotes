/*!
  分数小数化
  输入a,b,c,输出a/b的小数形式，精确保留到后c位
  a,b<=10^6, c<=100
  难点：
    1.正常的浮点数只有20多位有效数字，要处理到100位需要特殊的处理
    2.考虑四舍五入的问题
*/
#include <iostream>
#include <cmath>

using namespace std;

#define MAX_N 200

int main()
{
    //c中的每个子符存储'0'~'9',正好到0截止
    char c[MAX_N];
    int a, b, n,cnt;
    bool neg = false;
    int c0, c1, casen=0;
    do {
        cnt = scanf("%d%d%d", &a, &b, &n);
        n++; //考虑进位
        //cnt = 3;
        //a = 277, b=322, n=16;
        //a = 324, b=857, n=10;
        if(cnt != 3 || b == 0 || n < 0) break;
        if(a < 0 || b < 0) {
            neg = true;
            a = abs(a);
            b = abs(b);
        }

        c0 = a/b; //得到整数部分
        c1 = a%b; //得到余数
        int i,j;
        char buf[MAX_N*2];
        for(i=0; i<n && c1 != 0; ) {
            j = c1 * 10;
            while(j < b && i<n) {
                j *= 10; //j = c1*10 ERROR
                c[i++] = '0';
                if(i == n) break; //这里可能会溢出，没有考虑仔细
            }
            if(i == n) break;
            c[i++] = '0' + j/b;
            c1 = j%b;
        }
        c[i]=0;
        if(i==0) {
            sprintf(buf,"%s%d",neg?"-":"", c0);
        } else {
            //进位,i==n的时候执行进位,没有考虑进位
            if(i ==n ) {
                //i==n，必须去掉最后一位,如果最后一位大于5，还要对最后一位进行进位（逐步进行)
                if(c[i-1] >= '5') {
                    int k,x;
                    k=i-2, x=0;
                    for(; k>=0;) {
                        x = c[k] - '0';
                        if(x+1 < 10) {
                            c[k] = x+1+'0';
                            break;
                        } else {
                           --k;
                        }
                    }

                    //进位一直推进到整数位
                    if(k < 0) {
                        c0++;
                    }
                }
                c[i-1]=0; //去掉最后一位
            }
            sprintf(buf,"%s%d.%s", neg?"-":"", c0,c);
        }

        printf("Case %d:%s\n", ++casen,buf);

    } while(true);
    return 0;
}
