#!/bin/bash

if [ $# -ne 2 ];then
    echo "wrong argument count"
    exit 1
fi

r=`find $1 -newer $2`
if [ -z "${r}" ];then
    exit 1
fi

exit 0
