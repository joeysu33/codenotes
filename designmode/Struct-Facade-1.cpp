/*!
 * 设计模式 外观(Facade)
 * 角色：
 * 1.很多个独立处理部分功能的角色
 * 2.构建一个Facade角色（来统一处理)
 * 3.客户角色
*/

#include <string>
#include <cstdio>
#include <cassert>
#include <iostream>

/*!
 * 细粒度功能类，实现整数的加减乘除
 */
class Plus {
public:
    static int add(int a, int b) { return a+b; }
};

class Minus {
public:
    static int minus(int a, int b) { return a-b;}
};

class Multipy {
public:
    static int multipy(int a, int b) { return a*b; }
};

class Divide {
public:
    static int divide(int a, int b) { assert(b); return a/b; }
};

/*
 * Facade角色，给所有的操作实现一个公共处理的接口类
 * 将功能统一聚合
 */
class Calculator {
public:
    static int add(int a, int b) { return Plus::add(a,b); }
    static int minus(int a, int b) { return Minus::minus(a,b);}
    static int multipy(int a, int b) { return Multipy::multipy(a,b);}
    static int divide(int a, int b) { return Divide::divide(a,b); }
};

/*!
 * 客户
 * 计算公式10+(2-8)*30/6
 */
class Client {
public:
    void calc1() {
        Plus plus;
        Minus minus;
        Multipy mul;
        Divide div;
        fprintf(stdout, "calc1 10+(2-8)*30/6=%d\n",plus.add(div.divide(mul.multipy(minus.minus(2,8),30),6), 10));
    }

    void calc2() {
        Calculator c;
        fprintf(stdout, "calc2 10+(2-8)*30/6=%d\n", c.add(c.divide(c.multipy(c.minus(2,8),30),6), 10));
    }
};

int main() {
    Client c;
    c.calc1();
    c.calc2();

    return 0;
}


