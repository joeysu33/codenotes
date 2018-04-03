#define _GNU_SOURCE

#include <sys/utsname.h>
#include <stdio.h>

int
main(int argc, char *argv[]) {
    struct utsname name;
    if(uname(&name) == -1) {
        fprintf(stderr, "error:%s", "uname");
        return 1;
    }

    printf("sysname:%s\n"
            "nodename:%s\n"
            "release:%s\n"
            "version:%s\n"
            "machine:%s\n"
            "domainname:%s\n", 
            name.sysname,
            name.nodename,
            name.release,
            name.version,
            name.machine,
            name.domainname);

    return 0;
}
