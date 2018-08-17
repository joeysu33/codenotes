/*!
 * DP算法(Dynamic Planning|Programming)主要是将问题转换成DAG
 * (Directed Acylic Graph)有向无环图。并辅以存储来缓存子问题
 * 的结果来达到动态规划的效果
 *
 * 01背包问题，有m种的物品，每个物品仅一个，每个物品的重量是w[i], 价值是p[i],
 * 现在背包的容量是C，问应该如何选择物品能达到最大价值(总体最优)。
 * 状态转换方程
 * f[i][j] = max { f[i-1][j], f[i-1][j-w[i]] + p[i] };
 * f[i][j] 表示第i种物品加入后，剩余重量j
 * f[i-1][j] 表示如果不放入第i种物品，则最大价值
 * f[i-1][j-w[i]] + p[i] 表示放入第i种物品，则最大价值
 *
 * 问题规模:将背包的负重从1开始一直到C (还是自底向上的原则来进行解题)
 * 存在的问题，背包问题和物品重量的粒度有关系，最小粒度的取值必须是其他所有背包的除数。
 *
 * 一维数组转换方程
 * fa[j] = cmax(fa[j-1] , fa[j-w[i]] + p[i]);
 */

#include "common.h"

#define NMAX 120
#define NVAL 16

int
main(int argc, char *argv[]) {
    int i, st, j, k, m, n,f[NMAX][NMAX], w[NMAX], p[NMAX];

    memset(f, 0, sizeof(f));
    memset(w, 0, sizeof(w));
    memset(p,0, sizeof(p));

    //printf("Enter the capacity of package and numbers of kind of package:");
    //fflush(stdout);
    scanf("%d%d",&n, &m); 
    //printf("Enter package names, weights, price.\n");
    //fflush(stdout);

    char c, *cp, str[NVAL], si, pkg[NMAX], selected[NMAX]; //si描述str的长度，足够了
    st = 0; 
    si = 0;
    j = 0;
    while( (c = fgetc(stdin)) != EOF) {
        if(isalpha(c) || isdigit(c)) {
            st = 1;
            pkg[j++] = c;
            break;
        }
    }

    i = 0;
    while((c = fgetc(stdin)) != EOF) {
        if(isalpha(c)) {
            if(i == 0)
                pkg[j++] = c; //物品名称就一个字符
        } else if(isdigit(c)) {
            str[si++] = c;
        } else if(c == '\n') {
            str[si] = 0;
            if(i == 1) {
                w[j++] = strtol(str, &cp, 0);
            } else {
                p[j++] = strtol(str, &cp, 0);
            }
            i++;
            j=0;
            si=0;
        } else if(isblank(c)) {
            str[si] = 0;
            if(i == 1) {
                w[j++] = strtol(str, &cp, 0);
            } else {
                p[j++] = strtol(str, &cp, 0);
            }
            si=0;
        } else {
            ;
        }
    }

    for(i=0; i<m; ++i) 
        printf("%-4c", pkg[i]);
    printf("\n");
    for(i=0; i<m; ++i) 
        printf("%-4d", w[i]);
    printf("\n");
    for(i=0; i<m; ++i) 
        printf("%-4d", p[i]);
    printf("\n");

    //i表示物品的种类,一般也会将i,j进行扩大一点,便于计算
    for(i=0; i<m; ++i) {
        //j表示物品的重量，step值取1
        for(j=1; j<=n; ++j) { //bugs-2 这里j是容量大小，应该取值到等于
            //第一次放物品
            if(i == 0) {
                if(j >= w[i]) 
                    f[i][j] =  p[i]; //bugs-1,这里f[i][j]表示的是最大价值,而不是w[i]
                else 
                    f[i][j] = 0;
            } else {
                if(j >= w[i]) 
                    f[i][j] = cmax(f[i-1][j], f[i-1][j-w[i]] + p[i]); //状态转移方程
                else 
                    f[i][j] = f[i-1][j];
            }
        }
    }

    for(j=1; j<=n; ++j) printf("%-4d ", j);
    printf("\n");
    for(i=0; i<m; ++i) {
        for(j=1; j<=n; ++j) {
            printf("%-4d ", f[i][j]);
        }
        printf("\n");
    }

    //找出选中的物品, 从下至上，从右至左，找到最后一个出现的最大值
    i = m-1; //最后一行
    j = n;
    while(i>=0 && j > 0) {
        //f[i][j] >= f[i-1][j]
        if(i-1 >= 0 && f[i-1][j] == f[i][j]) {
            --i;
            continue;
        }

        selected[k++] = pkg[i];
        j -= w[i];
        --i; //bugs-7 一行仅取值一次，取完就进入下一行
    }
    

    printf("\n");
    printf("Maximum value of package:%d\n", f[m-1][n]); //bugs-3, 要取到n值
    printf("Selected :");
    for(i=k-1; i>=0; --i) 
        printf("%c ", selected[i]);
    printf("\n");

    //使用一维滚轮数组来实现, fa表示在某个重量下能达到的最大价值
    int fa[NMAX];
    fa[0] = 0; //0表示没有重量
    for(i=0; i<m; ++i) {
        for(j=1; j<=n; ++j) {
            if(j >= w[i]) {
                fa[j] = cmax(fa[j-1], fa[j-w[i]] + p[i]);
            } else {
                fa[j] = fa[j-1];
            }
        }
    }
    printf("Maximum value of package:%d\n", fa[n]);

    return 0;
}


