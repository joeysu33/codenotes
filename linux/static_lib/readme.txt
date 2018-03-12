linux下的静态库的使用

1.将源代码编译成目标文件
    gcc -o string.o string.c
2.将目标文件转换成静态库
    ar -rcs string.a string.o
    ar Archive
    -rcs : r:替换重复符号
           c:创建归档文件
           s:创建符号

