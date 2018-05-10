#!/bin/bash

if [ $# -lt 1 ];then
    echo "参数太少"
    exit 1
fi

inc=$1
grep=''
if [ $# -ge 2 ];then
    grep=$2
fi

cc=`gcc -print-prog-name=cc1plus`
includes=`$cc -c -v /dev/null 2>&1 | awk '{if(index($0, " /")==1) print $0;}'`
for i in ${includes} ; do
    if [ -z ${grep} ]; then
        find ${i} -type f -iname "*${inc}*"
    else
        find ${i} -type f -iname "*${inc}*" -exec grep -inH ${grep} {} \;
    fi
done

exit 0
