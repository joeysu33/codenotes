/*!
 * 抽象工厂
 * 涉及到的角色
 * 1.产品
 * 2.工厂
 * 通过工厂类来创建产品
 */

#include <string>
#include <iostream>
#include <memory>
#include <cstdio>

using namespace std;
class Product;
typedef struct Size {
  Size(int w, int h) : width(w),height(h) {}
  int width, height;
} Size_t;

/*!
 * Products 
 */
class Product {
public:
  virtual ~Product() {}
  virtual string getName() const =0;
  virtual Size_t getSize() const =0;
  //....
};

class Candy : public Product {
public:
  string getName() const override { return "candy";}
  Size_t getSize() const { return Size_t(10,5); }
};

/*!
 * Product Factories
 */
class NoteBook : public Product {
public:
  string getName() const override { return "notebook"; }
  Size_t getSize() const override { return Size_t(800, 600); }
} ;

class ProductFactory {
public:
  virtual ~ProductFactory() {}
  virtual Product* create() = 0;
};

class CandyFactory: public ProductFactory {
public:
  static CandyFactory* instance() {
    static CandyFactory fac;
    return &fac;
  }

  Product* create() override { return new Candy(); }
private:
  CandyFactory() {}
  CandyFactory(const CandyFactory& o) ;
  CandyFactory& operator=(const CandyFactory&) ;
};

class NoteBookFactory : public ProductFactory {
public:
  Product* create() override { return new NoteBook(); }
};

namespace {
  void dump(const Product* p) {
    if(!p) return;

    Size_t s = p->getSize();
    string name = p->getName();
    fprintf(stdout, "name:%s, (width=%d, height=%d)\n", name.c_str(), s.width, s.height);
  }
}


int main() {
  NoteBookFactory fac;
  shared_ptr<Product> candy { CandyFactory::instance()->create()};
  shared_ptr<Product> notebook(fac.create());

  dump(candy.get());
  dump(notebook.get());

  return 0;
}





