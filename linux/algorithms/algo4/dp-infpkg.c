/*!
Dynamic Programming 无限背包
背包的容量上限C
每个物品的重量是w[i], 价值是p[i],
但是每个物品的数量是没有上限的
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

    scanf("%d%d",&n, &m); 
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

    int maxN[NMAX];
    //背包能存储某个物品的最大个数
    for(i=0; i<m; ++i) {
        maxN[i] = n / w[i];
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

    //无限背包的话，增加一种商品，直到该商品将背包塞满位置(尽可能多的放入该商品)
    int wi, pi, fi, wa[NMAX];
    char name[NMAX];
    fi=0;
    memset(name, 0, sizeof(name));

    for(i=0; i<m; ++i) {
        wi = w[i]; pi = p[i];
        for(k=0; k<maxN[i]; ++k, ++fi) {
            name[fi] = pkg[i];
            wa[fi] = wi;
            for(j=1; j<=n; ++j) { 
                if(fi == 0) {
                    if(j >= wi) 
                        f[fi][j] =  pi; 
                    else 
                        f[fi][j] = 0;
                } else {
                    if(j >= w[i]) 
                        f[fi][j] = cmax(f[fi-1][j], f[fi-1][j-wi] + pi); //状态转移方程
                    else 
                        f[fi][j] = f[fi-1][j];
                }
            }
        }
    }

    for(j=1; j<=n; ++j) printf("%-4d ", j);
    printf("\n");
    printf("\n");
    for(i=0; i<fi; ++i) {
        for(j=1; j<=n; ++j) {
            printf("%-4d ", f[i][j]);
        }
        printf("[%c]\n", name[i]);
    }

    //找出选中的物品, 从下至上，从右至左，找到最后一个出现的最大值
    i = fi-1; //最后一行
    j = n;
    k=0;
    while(i>=0 && j > 0) {
        if(i-1 >= 0 && f[i-1][j] == f[i][j]) {
            --i;
            continue;
        }

        selected[k++] = name[i];
        j -= wa[i];  //bugs-1 wa[i]而不是w[i]
        --i; 
    }
    

    printf("\n");
    printf("Maximum value of package:%d\n", f[fi-1][n]); //bugs-3, 要取到n值
    printf("Selected :");
    for(i=k-1; i>=0; --i) {
        printf("%c ", selected[i]);
    }
    printf("\n");

    return 0;

}
