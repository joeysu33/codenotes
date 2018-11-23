/*!
  vptr virtual table pointer
  vtbl virtual table
  vptr -> vtbl
*/

#include <iostream>
#include <cstdint>

using namespace std;

namespace {
    void showLine(const string& str ) {
        cout<<str<<endl;
    }
}

class A {
public:
    virtual ~A() {}
    virtual void foo() { showLine("A::foo()"); }
    virtual void bar() = 0;
};

class B : public A{
public:
    void foo() override { showLine("B::foo()");}
    void bar() override { showLine("B::bar()"); }
};

class C : public A{
public:
    void foo() override { showLine("C::foo()");}
    void bar() override { showLine("C::bar()"); }
};

class VB : virtual public A{
public:
    void foo() override { showLine("VB::foo()");}
    void bar() override { showLine("VB::bar()"); }
};

class VC : virtual public A{
public:
    void foo() override { showLine("VC::foo()");}
    void bar() override { showLine("VC::bar()"); }
};

class D : public VB, public VC {
public:
    void foo() override { showLine("D::foo()");}
    void bar() override { showLine("D::bar()"); }
};

uint64_t vtblAddr(void * p) {
    return *(uint64_t*)p;
}

template<class T>
void showObjVtblAddr(const string& name, T * obj) {
    cout<<std::hex<<name<<" 's vtbl=0x"<<vtblAddr(obj)<<endl;
}

int main()
{
    A *b1 = new B();
    A *b2 = new B();
    A *c1 = new C();
    A *c2 = new C();

    D * d = new D();
    VB *vb = d;
    VC *vc = d;
    A *a = d;
    showObjVtblAddr("d",d);
    showObjVtblAddr("vb",vb);
    showObjVtblAddr("vc",vc);
    showObjVtblAddr("a", a);

    showObjVtblAddr("b1",b1);
    showObjVtblAddr("b2",b2);
    showObjVtblAddr("c1",c1);
    showObjVtblAddr("c2",c2);

    delete d;
    delete b1; delete b2;
    delete c1; delete c2;

    return 0;
}
