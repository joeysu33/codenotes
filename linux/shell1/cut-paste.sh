#!/bin/bash

#理解并掌握cut, paste的用法，cut和paste是以列的形式来编辑文本

#取出/etc/passwd从1到10行的内容，并按照第一列取去
sed -n '1,10p' /etc/passwd | cut -d ":" -f 1 > username.txt
sed -n '1,10p' /etc/passwd | cut -d ":" -f 7 > userdir.txt
paste username.txt userdir.txt
paste -d ":" username.txt userdir.txt
rm -f username.txt userdir.txt

