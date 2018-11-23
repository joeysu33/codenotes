/*!
  拷贝构造函数语意
  有四种情况会生成nontrivial copy constructor
  1.含有非基础数据类型
  2.virtual function
  3.virtual base
  4.virtual base (may be not directly inheritance)
*/
#include <iostream>

using namespace std;

class NonTrivialCC1 {
private:
    string m_d;
};

class NonTrivialCC2 {
public:
    NonTrivialCC2() {}
    virtual ~NonTrivialCC2() {}
protected:
    virtual void foo() {}
};

class VB { public: virtual ~VB() {}};
class VC : virtual public VB {};
class NonTrivialCC3 : public VB {};
class NonTrivialCC4 : public VC {};

int main()
{
    NonTrivialCC1 cc1;
    NonTrivialCC2 cc2;
    NonTrivialCC3 cc3;
    NonTrivialCC4 cc4;

    return 0;
}

