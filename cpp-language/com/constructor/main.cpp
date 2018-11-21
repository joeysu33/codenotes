/*!
  C++编译器提供的隐式默认构造函数
  隐式默认构造函数分为两类
  (implicit defalut constructor)

  1.implicit trivail default constructor (隐式忽略构造函数)
  2.implicit nontrivail default construct (隐式重要构造函数)
     (1) 成员变量含类类型的, NonTrivial1
     (2) 含虚函数, NonTrivial2
     (3) 虚继承, NonTrivial3
     (4) 派生过程中，基类提供了默认构造函数的, NonTrivial4
*/
#include <iostream>
#include <string>

using namespace std;

class SimpleBase {
private:
    int x,y,z;
};

//===========implicit trival default constructor
class Trivial1 {

};

class Trivial2 {
private:
    int x, y, z; //非用户类类型的成员
};

//基类中未提供默认构造函数，且
//基类中不含虚函数，虚继承，
//基类中不含类类型的成员变量
class Trivial3 : SimpleBase {

};


//==========implicit nontrivial default constructor
class NonTrivial1 {
private:
    string m_text; //含有非基础类型的成员变量,需要调用string构造m_text
};

class NonTrivial2 {
 public:
    virtual void foo() { } //含有虚函数，需要构建vtbl, vptr
};

class Base {
 public:
    Base() { }
};

//基类提供了默认构造函数，但是派生类并未明确提供的情况
//提供构造函数，以调用基类的构造函数
class NonTrivial3 : public Base {

};

class X {
public:
    virtual ~X() {}
    virtual void foo() = 0;
};

//A和B均虚继承X
class A : virtual public X { public: virtual void foo() {}};
class B : virtual public X { public: virtual void foo() {}};

//存在虚继承
//          X
//      /      \
//   A         B
//       \     /
//    NonTrial4 (菱形结构)
class NonTrivial4 : public A, public B {
public:
    void foo() {}
};

int main()
{
    NonTrivial1 nt1;
    NonTrivial2 nt2;
    NonTrivial3 nt3;
    NonTrivial4 nt4;

    return 0;
}
