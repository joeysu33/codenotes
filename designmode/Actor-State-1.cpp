/*!
 * 设计模式-状态(State)
 * 在对象中聚合一个状态对象，根据
 * 状态对象的不同选择，来决定该对象的行为
 * 角色
 * 1.状态接口
 * 2.状态类
 * 3.使用状态的对象
 * 例子
 * 描述一个工具类作为一个状态类来表示交互操作对象
 * 当前应该执行的行为
 */

#include <initializer_list>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

using namespace std;

typedef class _Point { 
public:
    _Point() { assert(!m_x && !m_y);}
    _Point(int x, int y) :m_x(x),m_y(y) {}
    _Point(std::initializer_list<int> & i) {
        if(i.size() > 2) { assert(false); }
        auto ii=i.begin();
        if(ii != i.end()) {
            m_x=*ii; ii++;
        }

        if(ii != i.end()) {
            m_y=*ii;
        }
    }

    void setX(int x) { m_x=x; }
    int x() const { return m_x; }
    void setY(int y) { m_y=y; }
    int y() const { return m_y; }

    _Point operator-(const _Point& pt) const{
        _Point p;
        p.m_x=m_x-pt.m_x;
        p.m_y=m_y-pt.m_y;
        return p;
    }

    _Point operator+(const _Point& pt) const{
        _Point p;
        p.m_x=m_x+pt.m_x;
        p.m_y=m_y+pt.m_y;
        return p;
    }

    void invalidate() { m_x=-9999; m_y=-9999; }
    bool isValid() const { return m_x>=0 && m_y>=0; }
    friend ostream& operator<<(ostream& out, const _Point& pt) ;
private:
    int m_x{0}, m_y{0} ;
} Point;

ostream& operator<<(ostream& out, const _Point& pt) {
    out << "x="<<pt.m_x<<",y="<<pt.m_y;
    return out;
}


class MouseTool {
public:
    virtual ~MouseTool() {}
    virtual void mousePressed(const Point & pt) = 0;
    virtual void mouseReleased(const Point& pt) = 0;
    virtual void mouseMove(const Point& pt) = 0;
};

class MoveTool : public MouseTool{
public:
    void mousePressed(const Point& pt) override {
        m_lastPt = pt;
        cout<<"MoveTool::mousePressed"<<pt<<endl;
    }

    void mouseReleased(const Point& pt) override {
        if(!m_lastPt.isValid()) {
            return ;
        }

        Point p=pt-m_lastPt;
        cout<<"MoveTool::mouseReleased"<<pt<<endl;
    }

    void mouseMove(const Point& pt) override{
        cout<<"MoveTool::mouseMoveTo"<<pt<<endl;
    }
private:
    Point m_lastPt;
};

class EditTool : public MouseTool {
public:
    EditTool() {}
    void mousePressed(const Point& pt) override {
        m_lastPt = pt;
        cout<<"EditTool::mousePressed"<<pt<<endl;
    }

    void mouseReleased(const Point& pt) override {
        if(!m_lastPt.isValid()) {
            return ;
        }

        Point p=pt-m_lastPt;
        cout<<"EditTool::mouseReleased"<<pt<<endl;
    }

    void mouseMove(const Point& pt) override{
        cout<<"EditTool::mouseMoveTo"<<pt<<endl;
    }
private:
    Point m_lastPt;
};

typedef shared_ptr<MouseTool> MouseToolSP;

class GController{
public:
    GController() {}
    void setTool(const MouseToolSP& t) { 
        if(!t) return ;
        m_tool = t;
    }

    MouseToolSP getTool() const { return m_tool; }
protected:
    void mousePressEvent(const Point &pt) {
        if(m_tool) m_tool->mousePressed(pt);
    }

    void mouseReleaseEvent(const Point& pt) {
        if(m_tool) m_tool->mouseReleased(pt);
    }

    void mouseMoveEvent(const Point& pt) {
        if(m_tool) m_tool->mouseMove(pt);
    }

    friend int main();
private:
    MouseToolSP m_tool;
};


int main() {
    vector<Point> vp1 {{30,30}, {30,35}, {30,36}, {40, 45}, {80, 80}};
    vector<Point> vp2 {{20,20}, {30,75}, {30,56}, {60, 85}};
    GController ctrl;
    
    /*!
     * 使用工具1的状态
     */
    ctrl.setTool(MouseToolSP(new MoveTool));
    ctrl.mousePressEvent(vp1[0]);
    auto i1=vp1.begin() + 1, i2=vp1.end() -1;
    while(i1 != i2) {
        ctrl.mouseMoveEvent(*i1);
        ++i1;
    }
    ctrl.mouseReleaseEvent(*i1);

    cout<<endl;
    /*!
     * 使用工具2的状态
     */
    ctrl.setTool(MouseToolSP(new EditTool));
    ctrl.mousePressEvent(vp2[0]);
    i1=vp2.begin() + 1, i2=vp2.end() -1;
    while(i1 != i2) {
        ctrl.mouseMoveEvent(*i1);
        ++i1;
    }
    ctrl.mouseReleaseEvent(*i1);

    return 0;
}


