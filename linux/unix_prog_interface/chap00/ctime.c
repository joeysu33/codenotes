/*!
 * 本测试程序的作用是测试c函数中返回指针的，一般都已经分配了固定的缓存
 * 重复调用之前的数据会被清空
 * 类似函数:
 * getpwdent
 * getgrpevt
 * ctime等
 */
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int i=5;
    time_t t;
    while(i--) {
        t = time(NULL);
        printf("ctime=%s ctime=%p\n", ctime(&t), ctime(&t));
        sleep(1);
    }
    return 0;
}
