/*!
 * 创建型设计模式-原型
 * 角色
 * 1.客户(使用原型类的角色)
 * 2.原型(含有自我复制的虚接口),调用复制之后产生新的对象
*/

#include <string>
#include <memory>
#include <cstdio>
#include <cassert>
#include <vector>
#include <random>
#include <initializer_list>

using namespace std;

struct Point {
  Point() :m_x(0),m_y(0) {}
  Point(int x, int y) : m_x(x),m_y(y) {}
  Point(const initializer_list<int> &i) {
    if(i.size() != 2) assert(false);
    auto it = i.begin();
    m_x = *(it++);
    m_y = *(it++);
  }

  int m_x,m_y;
};

class Graphic {
public:
  virtual ~Graphic() {}
  virtual string getName() const { return "Graphic"; }
  virtual Graphic* clone() const = 0;

  void moveTo(const Point& pt) { m_pos = pt;}
  const Point& getPosition() const { return m_pos;}

  void describ() const {
    fprintf(stdout, "name:%s pos.x=%d pos.y=%d pointer=0x%08x\n",
        getName().c_str(), m_pos.m_x, m_pos.m_y, const_cast<Graphic*>(this));
  }
private:
  Point m_pos;
};

class Circle : public Graphic {
public:
  string getName() const override { return "Circle";}
  Graphic* clone() const override { return new Circle; }
};

class Rectangle : public Graphic {
public:
  string getName() const override { return "Rectangle";}
  Graphic* clone() const override { return new Rectangle;}
};

/*!
 * interaction client
 */
class Manipulator {
public:
  void select(Graphic * g) { m_graphic = g; }
  Graphic* getCurrentGraphic() const { return m_graphic; }

  Graphic* cloneMove(Graphic* g, const Point& newPos) {
    if(!g) return nullptr;
    Graphic* ng = g->clone();
    if(!ng) return nullptr;

    /*!设置新的图元，作为当前图元*/
    m_graphic = ng;
    m_graphic->moveTo(newPos);

    return ng;
  }
  
  bool move(Graphic* g, const Point& newPos) {
    if(!g) return false;
    g->moveTo(newPos);
    return true;
  }
private:
  Graphic *m_graphic;
};


int main() {
  Manipulator manipluator;
  vector<Graphic*> gs {new Rectangle, new Circle, new Circle, new Rectangle,
    new Rectangle, new Circle };
  default_random_engine eng;
  uniform_int_distribution<int> dis(0,gs.size());

  for(int i=0; i<3; ++i) {
    int r = dis(eng);
    manipluator.select(gs[r]);
    Graphic* ng = manipluator.cloneMove(manipluator.getCurrentGraphic(), Point(100,200));

    ng->describ();
    /*! 释放*/
    //delete ng;
    gs.push_back(ng);
    manipluator.select(nullptr);
  }

  for(auto i=gs.begin(); i != gs.end(); ++i) 
    delete *i;

  return 0;
}



