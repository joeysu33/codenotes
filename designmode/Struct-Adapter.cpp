#include <iostream>
#include <string>
#include <cstdio>
#include <cassert>

/*!
 * 结构型设计模式-适配器
Role:
1.Target
2.Adaptee
3.Client
*/

using namespace std;
class Adaptee {
public:
  void drawRectangle() const { fprintf(stdout, "Adaptee draw rectangle.\n"); }
  void drawCircle() const {fprintf(stdout, "Adaptee draw circle.\n"); }
};

class Target {
public:
    virtual void drawRect() const = 0;
    virtual void drawCircle() const = 0;
};

class AdapterTarget : public Target{
public:
    void drawRect() const override { m_adaptee.drawRectangle(); }
    void drawCircle() const override { m_adaptee.drawCircle(); }
private:
    Adaptee m_adaptee;
};

class Client {
public:
    void use(Target *t ) {
        if(!t) return;
        t->drawRect();
        t->drawCircle();
    }
};

int main() {
    AdapterTarget at;
    Client c;
    c.use(&at);

    return 0;
}


