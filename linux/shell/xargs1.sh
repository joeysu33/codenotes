#!/bin/bash

#xargs -0 (--null)以0作为结尾，对于文件名中含有空格的可以这样操作
#file1和file2的文件命中含有空格
#find 查找到指定的文件之后默认使用换行符来列出已经查找到的文件
#可以使用-print0将换行符修改为空字符 -print0和xargs -0来对应进行使用

#一般情况下文件名称最好加上"",避免特殊字符，例如空格之类的
function makefile() {
    if [ ! -f "$1" ];then
        echo "file1" >> "$1"
    fi
}

file1="file1 .log"
file2="file2 .log"

makefile "$file1"
makefile "$file2"

echo "使用find . -iname \"*.log | xargs rm\"无法删除"
find . -iname "*.log" | xargs rm
echo "应该使用 find . -iname \"*.log -print0 | xargs -0 rm\"可以删除"
find . -iname "*.log" -print0 | xargs -0 rm
exit 0

