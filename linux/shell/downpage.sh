#!/bin/bash

if [ $@ -lt 2 ]; then
    echo "参数太少 $0 [down_url] [down_url]"
    exit 1
fi

until [ $# -eq 0 ]; do
    echo "正在下载的URL地址:$1"
    wget -P . $1
    shift
done




