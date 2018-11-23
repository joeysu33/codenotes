/*!
   虚函数表的代价*/
#include <iostream>

using namespace std;

#define SHOWSIZE(cls) \
    do {\
        printf("sizeof("#cls")=%lu\n", sizeof(cls));\
    }while(0)

class ClassA {
public:
    virtual ~ClassA();
private:
    char x;
}; //16bytes in 64bit-machine

class ClassB {
private:
    char x;
}; //1 byte in 64-machine

class Empty {
}; // 1 byte in 64-machine

class C {
public:
    virtual ~C() {}
};

class C1 { public:  virtual ~C1() {}};

class D1 : virtual public C {
}; //8bytes

class D2 : virtual public C {
}; //8bytes

class D3 : public D1, public D2 {
}; //16 bytes

class D4 : public D3, public Empty {}; //16 bytes
class D5 : public D3, public  C1 {}; //24 bytes

class E {
public:
    virtual ~E() {}
}; //8bytes
class F {
public:
    virtual ~F() {}
}; //8bytes
class H : public F {}; //8bytes
class G : public E, public F {}; //16bytes
class I : public H , public E{};  //16bytes
class J : public I, public C1 {}; //24bytes
class K : public I, public C1 { private : char x;}; //32bytes
class L : public I, public C1 { private : int x;}; //32bytes

int main()
{
    SHOWSIZE(ClassA);
    SHOWSIZE(ClassB);
    SHOWSIZE(Empty);

    SHOWSIZE(D1);
    SHOWSIZE(D2);
    SHOWSIZE(D3);
    SHOWSIZE(D4);
    SHOWSIZE(D5);

    SHOWSIZE(E);
    SHOWSIZE(F);
    SHOWSIZE(G);
    SHOWSIZE(H);
    SHOWSIZE(I);
    SHOWSIZE(J);
    SHOWSIZE(K);
    SHOWSIZE(L);

    return 0;
}
