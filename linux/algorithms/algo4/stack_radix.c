/*
 * 栈的应用
 * 1.进制转换
 */

#include <stdio.h>

int
convert(unsigned int x, int base, char *out, int len) {
    if(base < 2 || base > 16) return 0;
    if(!out && len < 1) return 0;

    static char numtbl[] = { '0', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    
    char tmp[1024];
    int top = -1;

    /* 包含了x==0情况的处理 */
    do {
        tmp[++top] = numtbl[x % base];
        x /= base;
    } while(x > 0);

    if(top+2 > len) return 0;

    int j;
    for(j=0;top >= 0; ) {
        out[j++] = tmp[top--];
    }
    out[j] = 0;

    return 1;
}

int
main(int argc, char *argv[]) {
    int num, base;
    char buffer[1024];

    do {
        scanf("%d%d", &num, &base);
        if(num < 0) break;

        if(convert(num, base, buffer, 1024)) {
            printf("%s\n", buffer);
        } else {
            printf("Can not convert!\n");
        }
    } while(1);

    return 0;
}
