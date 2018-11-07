/*!
 * N皇后问题
 */

#include <stdio.h>

#define N 8

static int q[N];

int canPlace(int index) {
    int i;
    if(index == 0) return 1;
    for(i=0; i<index;++i) {
        if(q[i] == q[index] ||
                (i + q[i]) == (index + q[index]) ||
                (i - q[i]) == (index - q[index]))
            return 0;
    }
    return 1;
}

void
showPlace() {
    int i,j;
    static int k = 0;
    printf("------count:%d--------\n", ++k);
    fflush(stdout);
    for(i=N-1; i>=0; --i) {
        for(j=0; j<N; ++j) {
            if(q[i] == j) printf("%-2c",'@');
            else printf("%-2c", '*');
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);
    //getchar();
}

void
placeQueue(int index) {
    if(index < 0 || index > N) return;
    if(index == N) {
        showPlace();
        //TODO 这里没有返回，导致index ==N的时候仍然在执行
        //静态数据正好在q[N]的后面，且都是整型，导致静态数据被修改
        return ;
    }

    /*
     * 这么写会输出答案，但是答案很多
    if(q[index] == N) {
        q[index]=0;
        q[index-1]++;
        //递归不能出现回头回溯，否则调用重复
        placeQueue(index-1);
    }

    if(!canPlace(index)) {
       q[index]++;
       //不能自己调自己
       placeQueue(index);
    } else {
       //正确的递归
       placeQueue(index+1);
    }
    */

    //showPlace();
    for(int i=0; i<N; ++i) {
        q[index] = i;
        if(canPlace(index)) {
            placeQueue(index+1);
        }
    }
}


int
main(int argc, char *argv[]) {
    int i;
    for(i=0; i<N; ++i) q[i] = 0;
    placeQueue(0);
    /*
     * 为啥没有这行?
    for(i=0; i<N; ++i) {
        q[0]=i;
        placeQueue(0);
    }*/
    return 0;
}



