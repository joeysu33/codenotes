#!/usr/bin/awk -f

BEGIN {
    print("Envrionments:");
    #打印环境变量
    for(i in ENVIRON) {
        printf("ENVIRON[%s]=%s\n", i, ENVIRON[i]);
    }
    #打印参数
    for(i in ARGV) {
        printf("ARGV[%s]=%s\n", i, ARGV[i]);
    }
    #使用循环打印
    for(i=0; i<ARGC;++i) {
        printf("ARGV[%s]=%s\n", i, ARGV[i]);
    }
}
