/*!
 * DP最长子序列问题
 * LCS Longest Common Sequence
 * 算法复杂度O(m*n)
 *
 * 确定状态转移方程:
 * A1,A2,,,, B1,B2,B3,,,
 * 如果A[i] == B[j], 则d[i][j] = d[i-1][j-1] + 1
 * 否则 d[i][j] = max(d[i-1][j], d[i, j-1]);
 */
#include "common.h"

#define NNUM 16
#define NMAX 1024

int
main(int argc, char *argv[]) {
    char c, num[NNUM], sa[NMAX], sb[NMAX], *cp;
    int st = 0, i, j, k, len[2];

    i=0; len[0] = len[1] = -1;
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
            k = 0;
        }
    }

    printf("sa:");
    for(i=0; i<len[0]; ++i) printf("%-4d", sa[i]);
    printf("\nsb:");
    for(i=0; i<len[1]; ++i) printf("%-4d", sb[i]);
    printf("\n");

    return 0;
}

