#include <cstdio>
#include <iostream>
#include <typeinfo>

using namespace std;

class Y {
public:
    Y(int v=0):m_v(v) {}
    int m_v {0};
};

class X {
public:
    X(int v=0):m_v(v) {}
    X operator+(const Y& y) {
        return X(y.m_v + m_v);
    }
    int m_v {0};
};

class Z {
public:
    Z(int v=0):m_v(v) {}
    Z operator+(const Y& y) {
        return Z(y.m_v + m_v);
    }

    Y operator+(const X& x) {
        return Y(x.m_v + m_v);
    }
    int m_v {0};
};


//模版的变长参数
template<typename ...Args>
void magic(Args... args) {
    int argsCnt = sizeof...(args);
    cout<<argsCnt<<endl;
}

//自动返回类型推倒(C++11 style)
template<class T, class U>
auto add(T x, U y) -> decltype(x+y) {
    cout<<"add return type:"<<typeid(decltype(x+y)).name()<<endl;
    return x+y;
}

//自动返回值类型推导(C++14 Style)
template<class T, class U>
auto add2(T x, U y) {
    cout<<"add2 return type:"<<typeid(decltype(x+y)).name()<<endl;
    return x+y;
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    //边长模版参数
    magic();
    magic(10);
    magic(100, X(20));
    magic(100, X(20), Y(30));
    magic(100, X(20), Y(30), Z(40));

    add(X(10), Y(20));
    add2(Z(40), Y(50));
    add2(Z(20), X(30));
    return 0;
}










