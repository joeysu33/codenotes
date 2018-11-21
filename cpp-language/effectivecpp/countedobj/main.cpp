/*!
 可计数对象类实现
 private继承，将基类作为数据来使用
 可以通过 using BaseClass::<member>来开放基类的接口
*/
#include <iostream>
#include <exception>
#include <stdexcept>
#include <memory>
using namespace std;

class CountExceed : public std::logic_error {
public:
    explicit CountExceed(const string& ex) : logic_error(ex) {}
};

//class Tag仅仅作为一个标签，并不参与类的操作
//仅仅作为一个技巧，模板化Counted成为很多不同的类
template<class Tag>
class Counted {
public:
    bool canCreate() const { return m_numObj < m_maxObj; }
    int getMaxCount() const { return m_maxObj; }
protected:
    Counted() {
        ++m_numObj;
        if(m_numObj > m_maxObj) {
            throw CountExceed("CountedExceed");
        }
    }
    ~Counted() {
        --m_numObj;
    }
private:
    static int m_maxObj;
    static int m_numObj;
};

//初始化m_numObj,m_maxObj留给派生类实现
template <class Tag> int Counted<Tag>::m_numObj = 0;


//私有继承Counted<Printer>，仅仅作为一个统计数据
class Printer : private Counted<Printer> {
public:
    static Printer* newPrinter()  { return new Printer(); }

    //使用using将基类private的函数提升到public
    using Counted<Printer>::canCreate;
    using Counted<Printer>::getMaxCount;

private:
    Printer() {}
private:
    Printer(const Printer& p);
    Printer& operator=(const Printer& p);
};

#define N 3

//初始化类的静态变量m_maxObj，默认特化需要template<>
template<> int Counted<Printer>::m_maxObj = N;

int main()
{
    Printer *p[N];
    for(int i=0; i<N; ++i)
        p[i] = Printer::newPrinter();

    //尽量使用只能指针，在异常的时候能自动析构释放资源
    shared_ptr<Printer> p1;
    try {
        p1.reset(Printer::newPrinter()); //error
    } catch(const logic_error& ex) {
        cout<<"exception="<<ex.what()<<endl;
    }

    for(int i=0; i<N; ++i) { delete p[i]; p[i] = nullptr; }

    return 0;
}

