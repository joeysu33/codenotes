#!/bin/bash

if [ $# -ne 2 ];then
    echo "Wrong argument count"
    exit 1
fi

if [[ ! -f $1  || ! -f $2 ]]; then
    echo "File is not exist"
    exit 2
fi

r=`find $1 -newer $2`
if [ -z "${r}" ];then
    exit 1
fi

exit 0
