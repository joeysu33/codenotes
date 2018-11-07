/*!
 * DP最长子序列问题
 * LCS Longest Common Sequence
 * 算法复杂度O(m*n)
 *
 * (拓展)
 * LCS(Longest Common Sequence)和LCS(Longest Common Substring)不是一个意思。
 * 最长公共子序列是指在序列中移除某些元素之后的顺序列表（非集合，集合是无序的），
 * 最长公共子串，是一段"连续"的子字符串,也就是最长公共子序列可以是不连续的串，
 * 也就是最长公共子串算是最长公共子序列的特例。
 *
 * 确定状态转移方程:
 * A1,A2,,,, B1,B2,B3,,,
 * 如果A[i] == B[j], 则d[i][j] = d[i-1][j-1] + 1
 * 否则 d[i][j] = max(d[i-1][j], d[i, j-1]);
 */
#include "common.h"

#define NNUM 16
#define NMAX 1024

void
showTable(int t[][NMAX], int xsize, int ysize) {
    int i, j;
    for(i=1; i<=ysize; ++i) {
        printf("%-2d ", i);
    }
    printf("\n\n");

    for(i=1; i<=xsize; ++i) {
        for(j=1; j<=ysize; ++j) {
            printf("%-2d ", t[i][j]);
        }
        printf("\n");
    }
}

int
main(int argc, char *argv[]) {
    char c, num[NNUM] , *cp; 
    int sa[NMAX], sb[NMAX];
    int st = 0, i, j, k, len[2];

    i=0; len[0] = len[1] = -1;
    k=1;
    sa[0] = sb[0] = -1; //从1开始进行对齐
    while( (c = fgetc(stdin)) != EOF) {
        if(isdigit(c)) {
            num[i++] = c;
        } else if(c == ',') {
            num[i] = 0;
            if(st == 0) 
                sa[k++] = strtol(num, &cp, 0);
            else
                sb[k++] = strtol(num, &cp, 0);
            i = 0;
        } else if(c == '\n') {
            num[i] = 0;
            if(st == 0) {
                sa[k++] = strtol(num, &cp, 0);
                len[st] = k;
            } else {
                sb[k++] = strtol(num, &cp, 0);
                len[st] = k;
            }
            st++; if(st == 2) break;
            i = 0;
            k = 1;
        }
    }

    printf("sa:");
    for(i=1; i<len[0]; ++i) printf("%-2d ", sa[i]);
    printf("\nsb:");
    for(i=1; i<len[1]; ++i) printf("%-2d ", sb[i]);
    printf("\n");

    int f[NMAX][NMAX];
    for(i = 0; i<NMAX; ++i) f[0][i] = f[i][0] = 0;
    for(i=1; i<len[0]; ++i) {
        for(j=1; j <len[1]; ++j) {
            if(sa[i] == sb[j]) {
                f[i][j] = f[i-1][j-1] + 1;
            } else {
                f[i][j] = cmax(f[i-1][j], f[i][j-1]);
            }
        }
    }

    printf("Maxinum matched size:%d\n", f[len[0]-1][len[1]-1]);
    showTable(f, len[0]-1, len[1]-1);

    return 0;
}

