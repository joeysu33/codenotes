#include <iostream>
#include <memory>

using namespace std;

typedef int DataTy;

class Base1 {
public:
    virtual ~Base1() { cout <<"Base1::~Base1()"<<endl; }
    virtual void doSome() const = 0;
private:
    DataTy d1;
};

//纯虚函数也可以有实现
void Base1::doSome() const { cout <<"Base1::doSome()"<<endl; }

class Base2 {
public:
    virtual ~Base2() { cout <<"Base2::~Base2()"<<endl; }
    virtual void doSome() const { cout <<"Base2::doSome()" <<endl; }
private:
    DataTy d2;
};

class Derived : public Base1, public Base2 {
public:
    ~Derived() { cout <<"Derived::~Derived()"<<endl; }
    virtual void doSome() const { cout <<"Derived::doSome()"<<endl; }
private:
    DataTy d3;
};

void multiInherit() {
    shared_ptr<Derived> d(new Derived);
    Base1 *b1 = d.get();
    Base2 *b2 = d.get();
    cout<<"b1="<<b1<<" d="<<d.get() <<" b2="<<b2<<endl;
}

//---------------------------------------------------------------------------------------------------------
class Derived2 : public Base2 {
public:
    ~Derived2() { cout <<"Derived::~Derived()"<<endl; }
};

class Derived3 : virtual public Base2 {
public:
    ~Derived3() { cout <<"Derived::~Derived()"<<endl; }
};

void virtualInherit() {
   shared_ptr<Derived2> d2(new Derived2);
   shared_ptr<Derived3> d3(new Derived3);
   Base2 *b21 = d2.get();
   Base2 *b22 = d3.get();

   cout<<"b21="<<b21<<" d2="<<d2.get()<<endl;
   //虚继承会造成vtbl发生偏移
   cout<<"b22="<<b22<<" d2="<<d2.get()<<endl;
}

//---------------------------------------------------------------------------------------------------------
typedef void (Base1::*SomeFunc) () const;
void memberFunc() {
    shared_ptr<Derived> d (new Derived);
    SomeFunc sf = &Base1::doSome;
    //直接使用(d->*sf)()报错
    (d.get()->*sf)();
}

int main()
{
    multiInherit();
    virtualInherit();
    memberFunc();

    return 0;
}





