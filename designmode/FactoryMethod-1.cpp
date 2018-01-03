/*!
 * 工厂方法
 * 创建一类产品
 * 角色: 
 * 1.工厂
 * 2.产品
 */

#include <string>
#include <cstdio>
#include <cassert>
#include <memory>

using namespace std;

class Pen {
public:
  virtual ~Pen() {}
  virtual string getName() const { return "Pen"; }
  virtual void drawCircle() = 0;
  virtual void drawRectangle() = 0;
  virtual void drawTriangle() =0;
};

#define DRAWUSING(what) \
static void draw##what##Using(Pen *p) { \
  if(!p) return ;\
  fprintf(stdout, "draw "#what"using %s\n", p->getName().c_str());\
}

namespace {
  DRAWUSING(Circle)
  DRAWUSING(Rectangle)
  DRAWUSING(Triangle)
}

/*!铅笔*/
class Pencil : public Pen {
public:
  string getName() const override { return "Pencil"; }
  void drawCircle() override { drawCircleUsing(this); }
  void drawRectangle() override { drawRectangleUsing(this); }
  void drawTriangle() override { drawTriangleUsing(this); }
};

/*!圆珠笔*/
class BallPen : public Pen {
public:
  string getName() const override { return "BallPen"; }
  void drawCircle() override { drawCircleUsing(this); }
  void drawRectangle() override { drawRectangleUsing(this); }
  void drawTriangle() override { drawTriangleUsing(this); }
};

class Factory {
public:
  virtual ~Factory() {}
  virtual Pen* createPen() const = 0;
};

class PencilFactory : public Factory {
public:
  Pen* createPen() const  override { return new Pencil; }
};

class BallPenFactory : public Factory {
public:
  Pen* createPen() const override { return new BallPen; }
};

int main() {
  PencilFactory pf;
  BallPenFactory bpf;
  Pen* p1 = pf.createPen();
  Pen* p2 = bpf.createPen();

  p1->drawCircle();
  p2->drawCircle();

  delete p1;
  delete p2;

  return 0;
}




