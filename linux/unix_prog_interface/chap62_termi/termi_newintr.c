/*!
 * terminal set new intr (CTRL+?)
 *
 * struct termios {
 *  tcflag_t c_iflag; //输入flags
 *  tcflag_t c_oflag; //输出flags
 *  tcflag_t c_cflag; //控制flags
 *  ...
 *  cc_t c_cc[NCCS]; //终端特殊字符 Control Character
 *  ...
 * }
 */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

int 
main(int argc, char *argv[]) {
    int intr;
    char *endptr;
    struct termios tos;

    if(argc != 2) {
        fprintf(stderr, "%s <character (A-Z)>, A对应1.\n", argv[0]);
        return 0;
    }

    intr = strtol(argv[1], &endptr, 0);

    if(tcgetattr(STDIN_FILENO, &tos) < 0) {
        perror("tcgetattr");
        return EXIT_FAILURE;
    }

    tos.c_cc[VINTR] = intr;
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &tos) < 0) {
        perror("tcsetattr");
        return EXIT_FAILURE;
    }

    if(tcgetattr(STDIN_FILENO, &tos) < 0) {
        perror("tcgetattr");
        return EXIT_FAILURE;
    }

    if(tos.c_cc[VINTR] != intr) {
        printf("intr set failed.\n");
    } else {
        printf("intr set success!\n");
    }

    return 0;
}

