#!/usr/bin/awk -f

#awk执行命令，并将命令读入变量
BEGIN {
    #执行date命令，并将执行结果输入到变量数组d中
    "date" | getline d; 
    #对d进行默认的分割
    split(d,a); print(a[2]);
    for(i in a) {
        print(a[i], ",");
    }
}

