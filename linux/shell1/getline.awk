#!/usr/bin/awk -f


#测试awk中geline的用法
BEGIN {
    i=0;
    var=""
    while(i<5) {
        i+=1;
        getline var;
        print("var=", var);
    }
}

