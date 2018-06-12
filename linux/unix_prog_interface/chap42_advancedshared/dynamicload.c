#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> //dlopen dlinfo dlclose dlsym dlvsym

int 
main(int argc, char* argv[]) {
    void* handle;
    typedef void (*FUNC) (void);
    char *err;
    FUNC func;

    if(argc != 3) {
        fprintf(stderr, "%s <library_name> <function_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle = dlopen(argv[1], RTLD_LAZY);
    if(!handle) {
        fprintf(stderr, "dlopen()");
        return EXIT_FAILURE;
    }

    printf("%s:library is loaded [RTLD_LAZY]\n", argv[1]);
    dlerror(); //clear errors
    func = (FUNC)dlsym(handle, argv[2]);
    err = dlerror();
    if(err) {
        dlclose(handle);
        fprintf(stderr, "dlsym()");
        return EXIT_FAILURE;
    }

    printf("%s: symbol:%s, is parsed!\n", argv[1], argv[2]);
    (*func)();

    dlclose(handle);
    printf("close module:%s\n", argv[1]);
    return 0;
}
