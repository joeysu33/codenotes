/*!
 只允许在堆上创建对象
 so stupid usage
 */
#include <iostream>

using namespace std;

class HeapOnly {
public:
    HeapOnly() {}
    HeapOnly(int x) : m_x (x) {}

    void destroy() {
        this->~HeapOnly(); //WTF
        delete this; //so horrible
    } //so stupid
private:
    ~HeapOnly() {}
private:
    int m_x;
};

int main()
{
    //Never can make object on stack
//    HeapOnly h1;
//    static HeapOnly h3;

    HeapOnly *h2 = new HeapOnly(5);
    h2->destroy();

    return 0;
}
