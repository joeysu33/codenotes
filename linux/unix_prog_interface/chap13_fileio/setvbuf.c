/*!
 * stdio库中设置文件buffer的函数
 * setvbuf
 */

#include <stdio.h>
#include <ctype.h> //support isprint isletter

#define USE_LINE_BUF

int
main(int argc, char *argv[]) {
    char c;
    char buf[20] = {0};
    int i;

#if defined(USE_LINE_BUF)
    setvbuf(stdin, buf, _IOLBF, sizeof(buf));
#else
    setvbuf(stdin, buf, _IOFBF, sizeof(buf));
#endif

    while(1) {
        /*! getchar能读入换行符*/
        c = getchar();
        if(c == 'S') break;

        for(i=0; i<sizeof(buf); ++i) {
            if(isprint(buf[i])) {
                printf("[%c]", buf[i]);
            }
        }

#if defined(USE_LINE_BUF)
        printf("\n{%c}\n", c);
#else
        if(c != '\n')
            printf("\n{%c}\n", c);
        else
            printf("\n");
#endif
    }
    return 0;
}


