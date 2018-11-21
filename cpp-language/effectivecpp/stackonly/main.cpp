/*!
  只允许在栈上构建对象
  操作符重载私有化
  operator new
  operator new[]
  operator delete
  operator delete[]
*/
#include <iostream>

using namespace std;

class StackOnly {
public:
    StackOnly() {}
private:
    void* operator new(size_t s);
    void operator delete(void *s);
    void* operator new[] (size_t s);
    void operator delete[] (void *s);
    void* operator new(size_t s, void *loc); //replacement new
};

int main()
{
        StackOnly s1;

        //Forbbiden on heap to new object
//        void* loc = new char[sizeof(StackOnly)];
//        StackOnly *s2 = new StackOnly();
//        StackOnly *s3 = new StackOnly[5];
//        StackOnly *s4 = new (loc) StackOnly();
//        delete loc;

        return 0;
}
