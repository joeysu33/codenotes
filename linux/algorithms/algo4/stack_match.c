/*
 * 栈符号匹配
 */

#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[]) {
    char buf[1024];
    char *s, c;
    char stk[1024];
    char tbl[128];
    int top = -1;

    tbl[')'] = '(';
    tbl[']'] = '[';
    tbl['}'] = '{';

    do {
        scanf("%s", buf);
        if(!strcmp(buf, "exit")) break;
        s = &buf[0];

        top = -1;
        while(*s) {
            c = *s;
            if(c == '(' || c == '[' || c == '{') {
                if(top < -1) { top = 0; break; }

                stk[++top] = c;
            } else if(c == ')' || c== ']' || c== '}') {
                if(top < 0 || tbl[c] != stk[top]) {
                    top = 0;
                    break;
                } else { top--; }
            }
            ++s;
        }

        if(top == -1) {
            printf("matched.\n");
            fflush(stdout);
        } else {
            printf("Not matched.\n");
        }

    } while(1);

    return 0;
}
