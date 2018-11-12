/*!
 * Femat-Lagrange
 * 费马-拉格朗日定理
 * 任何一个自然数都可表示为4个整数的平方和
 * 例如 30 = 1^2 + 2^2 + 3^2 + 4^2
 * 使用回溯法来求解
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
//#define STEP

static int stk[N];

void 
showResult(int num) {
    if(!stk) return ;
    printf("%d = ", num);
    for(int i=0; i<N; ++i) {
        if(i == N-1) printf(" %d²", stk[i]);
        else printf(" %d² +", stk[i]);
    }
    printf("\n");
}

int canUse(int i, int num) {
    return (i*i <= num) ;
}

void
showStack(int level) {
    for(int i=0; i<N; ++i) {
        if(i<=level) printf("%-6d", stk[i]);
        else printf("%-6c", '*');
    }
    printf("\n");
    fflush(stdout);
#if defined(STEP)
    getchar();
#endif
}

int isOK(int value) {
    int sum = 0;
    for(int i=0; i<N; ++i) sum += stk[i] * stk[i];
    return (value == sum);
}

//返回一个解
int
fematLagrange_1(int num, int level, const int value) {
    showStack(level);

    if(level == N && isOK(value)) {
        return 1;
    }

    //最多只能有N层
    if(level > N) return 0;

    for(int i=sqrt(num); i>=0; --i) {
        stk[level] = i;
        if(fematLagrange_1(num - i*i, level+1, value)) return 1;
    }

    return 0;
}


//全解
void
fematLagrange(int num, int level, const int value) {
    if(level == N && isOK(value)) {
        showResult(value);
    }

    //最多只能有N层
    if(level > N) return ;

    for(int i=sqrt(num); i>=0; --i) {
        stk[level] = i;
        fematLagrange(num -i*i, level+1, value);
    }
}

int
main(int argc, char *argv[]) {
    int num, level, mode;
    char *cp;

    mode = 0;
    if(argc > 1) mode = strtol(argv[1], &cp, 0);

    do {
        scanf("%d", &num);
        level = 0;

        if(!mode) {
            if(fematLagrange_1(num, level, num)) {
                showResult(num);
            } else {
                printf("num=%d,无解\n", num);
            }
        } else {
            fematLagrange(num, level, num);
        }
    } while(num > 0);

    return 0;
}



