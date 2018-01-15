/*!
 * 结构型设计模式-装饰器(decorator)
 * 角色
 * 1.被装饰的对象
 * 2.用来包装被装饰器的对象
 * python中@装饰器也是采用这样的操作
 * 装饰器中的调用规则
 * --------------------
 * |装饰调用          |
 * |被装饰对象调用    |
 * |装饰调用          |
 * --------------------
 */

#include <string>
#include <iostream>
#include <cstdio>
#include <cassert>

/*!
 * 普通手机
 */
class Phone {
public:
  virtual ~Phone() {}
  virtual void looks() const { fprintf(stdout, "It's a common Phone.");}
};

class DecoretorForPhone : public Phone {
public:
    DecoretorForPhone(Phone* p) :m_phone(p) { assert(p != this); }
protected:
    Phone *m_phone{nullptr};
};

class BigScreenPhone : public DecoretorForPhone{
public:
    BigScreenPhone(Phone* p):DecoretorForPhone(p) {}
    void looks() const override { fprintf(stdout, "with 6-inch screen,"); m_phone->looks(); fprintf(stdout, "\n");}
};

class WifiPhone : public DecoretorForPhone{
public:
    WifiPhone(Phone* p) : DecoretorForPhone(p) {}
    void looks() const override { fprintf(stdout, "with wifi function,"); m_phone->looks(); fprintf(stdout,"\n");}
};

int main() {
    /*!
     * 通过BigScreenPhone和WifiPhone来装饰Phone*
     */
    Phone p;
    BigScreenPhone bp(&p);
    WifiPhone wp(&bp);
    wp.looks();

    return 0;
}








