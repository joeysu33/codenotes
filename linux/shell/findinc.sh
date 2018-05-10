#!/bin/bash

if [ $# -ne 1 ];then
    echo "参数太少"
    exit 1
fi

cc=`gcc -print-prog-name=cc1plus`
includes=`$cc -c -v /dev/null 2>&1 | awk '{if(index($0, " /")==1) print $0;}'`
for i in ${includes} ; do
    find ${i} -type f -iname "*$1*"
done
exit 0
