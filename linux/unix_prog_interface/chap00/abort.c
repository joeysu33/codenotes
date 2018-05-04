/*!
 * 测试abort并生成核心转储文件
 * 生成核心转储文件需要ulimit -c XXX
 * XXX 是0则不生成，XXX是核心转储文件的上限值
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main() {
    printf("test abort\n");
    abort();
    return 0;
}
