#!/bin/bash

#bash中的参数就是指的实际参数，从$1开始
if [ $# -ne 1 ];then
    echo "缺少参数: $0 chapter-name"
    exit 1
fi

if [ -d "$1" ]; then
    exit 0
fi

echo "创建目录:$1"
mkdir "$1"
if [ $? -ne 0 ]; then
    exit 1
else
    cp Makefile_template.mk "$1"
fi

exit 0

