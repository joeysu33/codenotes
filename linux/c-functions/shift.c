/*!
 * C语言的左移位和右移位
 */

#include <stdio.h>

#define SIGNED_PRINT(expr) \
    do {printf("(signed) "#expr"=%d\n", expr);} while(0)
#define UNSIGNED_PRINT(expr) \
    do {printf("(unsigned) "#expr"=%u\n", expr);} while(0)

#define PRINT_ALL(expr) \
    SIGNED_PRINT(expr);\
    UNSIGNED_PRINT(expr); \
    printf("\n");

int
main() {
    const unsigned u1 = 1;
    const unsigned u2 = -1;
    const signed su1 = 1;
    const signed su2 = -1;

    PRINT_ALL(u1);
    PRINT_ALL(u2);
    PRINT_ALL(su1);
    PRINT_ALL(su2);

    PRINT_ALL(u1 << 1);
    PRINT_ALL(u2 << 1);
    PRINT_ALL(su1 << 1);
    PRINT_ALL(su2 << 1);

    return 0;
}
