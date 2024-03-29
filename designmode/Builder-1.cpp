/*!
 * Builder模式
 * 涉及到的角色
 * 1.指导者(director)
 * 2.构建者(builder)
 * 3.产品(product)
 * *在指导者的指导下通过构建者来构建产品
 */

#include <string>
#include <memory>
#include <cstdio>
#include <cassert>
/*!使用c++11的新特性 initializer_list*/
#include <initializer_list>

using namespace std;

/*!
 * 产品的组成部分-地基
 */
struct Foundation {
  Foundation() {}
  Foundation(const initializer_list<int>& i) {
    if(i.size() != 4) { assert(false); }

    initializer_list<int>::iterator it = i.begin();
    m_maxSupportPress = *(it++);
    m_width = *(it++);
    m_length = *(it++);
    m_depth = *(it++);
  }

  /*!最大承受压力*/
  int m_maxSupportPress {0};
  /*!地基的长、宽、深度*/
  int m_width{0}, m_length{0}, m_depth {0};
};

/*!
 * 产品组成部分-建筑主体
 */
struct Body {
  Body() {}
  Body(const initializer_list<int>& i) {
    if(i.size() != 2) assert(false);
    auto it = i.begin();
    m_layerCount = *(it++);
    m_layerHeight = *(it++);
  }

  /*! 建筑主体的层数 */
  int m_layerCount {0};
  /*! 建筑每层的高度 */
  int m_layerHeight {0};
};

/*!
 * 产品(建筑)
 */
class Building{
public:
  void setName(const string& name) {m_name = name; }
  string getName() const { return m_name; }

  void setFoundation(const Foundation & fd) { m_found = fd; }
  const Foundation& getFoundation() const { return m_found; }

  void setBody(const Body& body) {m_body = body; }
  const Body& getBody() const { return m_body; }

  void describ() {
    fprintf(stdout, "建筑名称:%s, 地基:承压=%d 长=%d 宽=%d 深度=%d"
        ", 主体:层数:%d 层高:%d \n", m_name.c_str(),
        m_found.m_maxSupportPress, m_found.m_length, m_found.m_width,  m_found.m_depth,
        m_body.m_layerCount, m_body.m_layerHeight);
  }
private:
  /*!建筑名称*/
  string m_name;
  /*! 地基*/
  Foundation m_found;
  /*! 主体*/
  Body m_body;
};

/*!
 * Builder-接口类
 */
class Builder {
public:
  virtual ~Builder() {}
  virtual void buildFoundation() = 0;
  virtual void buildBody() = 0;
  virtual void setBuildingName(const string& name) = 0;
  virtual Building getResult() = 0;
};

class CommonBuiler : public Builder {
public:
  void setBuildingName(const string& name) override { m_building.setName(name); }
  Building getResult() override { return m_building; }
protected:
  Building m_building;
};

/*!
 * 中式建造师
 */
class ChineseBuilder : public CommonBuiler{
public:
  void buildFoundation() override{
    Foundation fd ={100,200,300,400 };
    m_building.setFoundation(fd);
  }
  
  void buildBody() override{
    Body body ={100,5};
    m_building.setBody(body);
  }

};

/*!
 * 欧式建造师
 */
class EuropeanBuilder : public CommonBuiler{
  void buildFoundation() override{
    Foundation fd ={10,20,30,40};
    m_building.setFoundation(fd) ;
  }

  void buildBody() override{
    m_building.setBody(Body {300,4});
  }
};

/*!
 * 设计师 director,设计师指导builder进行建造建筑,
 * 建造完成之后，由builder来交付
 */
class Director  {
public:
  void directBuilder(Builder *builder) {
    if(!builder) return;

    /*!让builder开始打地基*/
    builder->buildFoundation();
    /*!让builder开始建造主体*/
    builder->buildBody();
  }
};

int main() {
  /*!
   * 分别由中式建筑师来构建一个中式建筑、
   * 欧式建筑师来构建一个欧式建筑，具体
   * 如何建筑由设计师来进行指导
   */

  ChineseBuilder cBuilder;
  EuropeanBuilder eBuilder;

  cBuilder.setBuildingName("鸟巢");
  eBuilder.setBuildingName("比萨斜塔");

  Director d;
  d.directBuilder(&cBuilder);
  d.directBuilder(&eBuilder);

  Building b1 = cBuilder.getResult();
  Building b2 = eBuilder.getResult();
  b1.describ();
  b2.describ();

  return 0;
}



