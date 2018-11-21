/*!
  关于虚函数是否可以内联的问题
  1.虚函数可以inline
  2.但是指针或引用方式调用虚接口的时候，并不依赖于inline
*/
#include <iostream>

//#define WITH_INLINE
#define WITH_INLINE inline

using namespace std;

class Base {
public:
    virtual ~Base() {}
    WITH_INLINE virtual void foo() { cout << "Base::foo()"<< endl; }
private:
    int m_x;
};

class Derived : public Base {
public:
    WITH_INLINE void foo()  override { cout << "Derived::foo()" <<endl; }
private:
    int m_y;
};

class C1  {
public:
    inline void aa () { cout << "C1::aa()" << endl; }
    void bb() ;
};
void C1::bb() { cout << "C1::bb()" <<endl; }

class X {

};

class Y {
public:
    virtual ~Y() { cout <<"Y::~Y()"<<endl; }
};

int main()
{
    cout<<"sizeof(X)="<<sizeof(X)<<endl;
    cout<<"sizeof(Y)="<<sizeof(Y)<<endl;

    Base *b1 = new Derived();
    b1->foo();

    Derived d;
    d.foo();

    Base b2 = d;
    b2.foo();

    C1 c1;
    c1.aa();
    c1.bb();

    return 0;
}

