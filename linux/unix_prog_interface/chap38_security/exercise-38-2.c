/*!
 * 编写一个程序，实现和sudo一样的功能
 * 核心理解
 * 1.sudo程序的权限
 * ls -l /usr/bin/sudo
 * -wrs-rx--x  /usr/bin/sudo
 *
 *  说明sudo默认已经setuid为root权限了，已经设置为setuid权限的程序，如果发生修改
 *  则权限会丢失，（防止修改程序来替换进程权限)
 *
 * 实现方案：
 * 编写一个程序，并使用root权限来赋予该进程sudo权限，根据登录的用户不同
 * 来调用setuid,因为子进程会权限继承，所以可以设置子进程的权限
 *
 * 函数
 * int getuid();
 * void setuid(int uid);
 * void setXXXuid(int uid);
 * int getXXXuid();
 */

#define _GNU_SOURCE //support getresuid, getresgid

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>  //getpwent
#include <shadow.h> //getspent
#include <termios.h>

typedef enum Bool{
    false,
    true
}bool;

struct passwd*
getPasswd(const char *user, struct passwd *rpw)  {
    struct passwd *pw;

    /*!将passwd的entry指向开始位置*/
    setpwent();
    for(pw = getpwent(); pw; pw = getpwent()) {
        if(!strcmp(pw->pw_name, user)) {
            break;
        }
    }

    if(!pw) {
        return NULL;
    }

    memcpy(rpw, pw, sizeof(*pw));
    return rpw;
}

void
showUID() {
    uid_t ruid, euid, suid;
    if(getresuid(&ruid, &euid, &suid) < 0) {
        perror("getresuid");
        exit(EXIT_FAILURE);
    }

    printf("pid=%d ruid=%d euid=%d suid=%d\n",
            getpid(), ruid, euid, suid);
}

void
showGID() {
    gid_t rgid, egid, sgid;
    if(getresgid(&rgid, &egid, &sgid) < 0) {
        perror("getresgid");
        exit(EXIT_FAILURE);
    }
    printf("pid=%d rgid=%d egid=%d sgid=%d\n",
            getpid(), rgid, egid, sgid);
}

bool
isValidUser(const char *user) {
    struct passwd pw;
    return getPasswd(user, &pw) ? true : false;
}

void
enableTermiEcho(bool enable) {
    int setFlag ;
    //tcgetattr tc=>terminal control
    struct termios tp;
    if(tcgetattr(STDIN_FILENO, &tp) < 0) {
        perror("tcgetattr()");
        exit(EXIT_FAILURE);
    }

    setFlag = 0;
    if(enable) {
        if(!(tp.c_lflag & ECHO)) {
            tp.c_lflag |= ECHO;
            setFlag = 1;
        }
    } else {
        if(tp.c_lflag & ECHO) {
            tp.c_lflag &= ~ECHO;
            setFlag = 1;
        }
    }

    if(setFlag) {
        /*!TCAS Terminal Control Apply Settings*/
        if(tcsetattr(STDIN_FILENO, TCSANOW, &tp) < 0) {
            perror("tcsetattr()");
            exit(EXIT_FAILURE);
        }
    }
}

int 
main(int argc, char *argv[]) {
    char user[64];
    char buf[256];
    char *cp;
    if(argc < 2) {
        fprintf(stderr, "%s -u <user> program-file arg1 arg2 ... | %s program-file arg1 arg2...\n", argv[0], argv[0]);
        return 1;
    }

    strcpy(user, "root");
    if(!strcmp(argv[1], "-u")) {
        strcpy(user, argv[2]);
    }

    if(!isValidUser(user)) {
        fprintf(stderr, "[%s] is invalid username.\n", user);
        return 1;
    }

    showUID();
    showGID();
    
    snprintf(buf, sizeof(buf), "[%s] input your password:", user);
    printf("%s ", buf);
    fflush(stdout);

    enableTermiEcho(false);
    cp = fgets(buf, sizeof(buf), stdin);
    if(!cp) {
        enableTermiEcho(true);
        printf("fgets() error!");
        return EXIT_FAILURE;
    }

    enableTermiEcho(true);

    /*!准备开始校验密码*/
    printf("\npassword=%s", buf);

    return 0;
}


