#!/bin/bash

mkfile=Makefile_template.mk

#根据模板更新子项目的配置文件
for i in `find . -type d -iregex ".*chap.*" `; do
    #echo "cmp $mkfile $i"
    j="$i/Makefile"
    if [ ! -f $j ]; then
        #在``中加上!不管用
        #在命令的判断中，不建议加上[]
        if `cp -f $mkfile $j`;then
            :
        else
            echo "1.Copy failed: from $mkfile to $j"
        fi
        continue;
    fi

    #如果mkfile比$i新则成立，返回$mkfile
    #-n string 字符串不为空
    #-z string 字符串为空
    #-nt newer than
    #-ot older than
    #shell 空白语句:
    if [ $mkfile -nt $j ]; then
        if `cp -f $mkfile $j` ;then
            :
        else
            echo "2.Copy failed: from $mkfile to $j"
        fi
    fi
done
exit 0
