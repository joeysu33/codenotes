/*!
  C++对象的布局*/
#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <cassert>

using namespace std;

template<class Type, unsigned int N = 1>
class NPoint {
public:
    NPoint() {
        for(int i=0; i<N; ++i) {
            m_points[i] = 0;
        }
    }

    NPoint(Type *t, int cnt) {
        for(int i=0; i<N; ++i) {
            if(i < cnt) m_points[i] = t[i];
            else m_points[i] = 0;
        }
    }

    const Type operator[] (int index) const {
        if(index < 0 || index >= N) return Type();
        return m_points[index];
    }

    Type& operator[] (int index) {
        if(index < 0 || index >= N) return Type();
        return m_points[index];
    }

    unsigned getCount() const { return N; }
private:
    Type m_points[N];
};

class Base {
public:
    virtual ~Base() { cout<<"Base::~Base()"<<endl; }
    virtual void foo() {}
private:
    int m_x;
};

class Derived1 : public virtual Base {
public:
    ~Derived1() { cout<<"Derived::~Derived1()"<<endl; }
    void foo() override {}
private:
    int m_d1;
};

class Derived2 : public Base {
public:
    ~Derived2() { cout <<"Derived2::~Derived2()" <<endl; }
    void foo() override {}
};

int main(int argc, char *argv[])
{
    (void)argc; (void)argv;
    Base *d1 = new Derived1();
    Base *d2 = new Derived2();

    Derived1 *dd1 = dynamic_cast<Derived1*>(d1);
    Derived2 *dd2 = dynamic_cast<Derived2*>(d2);

    assert(sizeof(void*) == sizeof(uint64_t));
    uint64_t *p = reinterpret_cast<uint64_t*>(dd1);
    uint64_t addr1 = *p;
    printf("addr1=0x%llx\n", addr1);
    uint64_t *vtbl = reinterpret_cast<uint64_t*>(addr1);
    for(int i=0; i<3; ++i) printf("addr[%d]=0x%llx\n", i, *(vtbl+i));

//    void * vtbl = static_cast<void*>((*dd1));
//    type_info * ti = static_cast<type_info*>(*vtbl);
//    type_info *ti = static_cast<type_info*>(getPointerPointer(dd2));

//    const type_info *ti2 = &typeid(dd1);
//    const char *name = ti2->name();

    delete dd1;
    delete dd2;

    return 0;
}
