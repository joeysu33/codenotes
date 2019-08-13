"use strict"

x = 100; //必须声明x var x;

var y=200;
delete y; //不允许删除变量或对象

function f1(x,y) {};
delete f1; //不允许删除函数

function f1(x,x) {}; //不允许变量重名

var z=020; //不允许使用8进制
