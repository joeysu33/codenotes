/*!
 * 工厂方法-简单模式（非23中设计模式)
 * 因为设计模式都是基于面向对象的，而
 * 最基本，最简单的工厂方法仅仅是一个函数
 *
 * 工厂方法和抽象工厂的区别在于，抽象工厂
 * 创建多种不同类型的产品，每一类产品都有
 * 一个创建接口，而工厂方法仅创建一类不同
 * 类型的产品。
 *
 * 简单工厂方法和工厂方法的区别在于，简单
 * 工厂方法仅仅用一个参数函数来描述，而
 * 工厂方法需要通过继承工厂角色来进行具体实现
 */

#include <string>
#include <memory>
#include <cstdio>

using namespace std;

class Product {
public:
  virtual ~Product() {}
  void setName(const string& name) { m_name = name; }
  virtual string getName() const { return m_name; }

  void describ() const {
    fprintf(stdout, "产品名称:%s, 宽:%d 高:%d 重量:%f\n",
        getName().c_str(), width(), height(), weight());
  }

  /*!单位mm*/
  virtual int width() const = 0;
  /*!单位mm*/
  virtual int height() const = 0;
  /*!单位g*/
  virtual float weight() const = 0;
private:
  string m_name;
};

class Candy : public Product {
public:
  int width() const override { return 10; }
  int height() const override { return 2; }
  float weight() const override { return 2.5; }
  string getName() const override { return "Candy"; }
};

class Car : public Product {
public:
  int width() const override { return 3000; }
  int height() const override { return 1200; }
  float weight() const override { return 2000000.3;}
  string getName() const override { return "Car"; }
};

enum ProductType {
  PT_Candy,
  PT_Car,
};

/*!
 * 简单工厂方法
 */
Product* createProduct(int type) {
  switch(type) {
    case PT_Candy: return new Candy;
    case PT_Car: return new Car;
    default: return nullptr;
  }

  return nullptr;
}

int main() {
  Product* p1 = createProduct(PT_Candy);
  Product* p2 = createProduct(PT_Car);

  p1->describ();
  p2->describ();

  delete p1;
  delete p2;
  return 0;
}




