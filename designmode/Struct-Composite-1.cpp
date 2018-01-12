/*!
 * 设计模式，结构型-组合
 * Composite
 * 角色
 * 1.组件
 * 2.叶子节点（不含子节点)
 * 3.组合节点
 *
 * 知识点:
 * 1.不要在父类构造或者析构函数中调用虚函数
 * 2.std::vector erase remove
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>

using namespace std;
#define NEWLEAF(name)\
    class name : public Leaf {\
    public:\
        void dobuleClick() override { fprintf(stdout, #name"::dobuleClick()\n"); }\
        void click() override { fprintf(stdout, #name"::click()\n");}\
        string getName() const override { return #name; }\
    };

class Component {
public:
    virtual ~Component() {
        fprintf(stdout, "~free:%s\n", getName().c_str());

        /*
         *        
         *错误写法，在父类析构函数中如此实现
         for(int i=getChildCount()-1; i>=0; --i) {
            if(Component *c = getChild(i)) {
                delete c;
            }
        }
        */
    }

    virtual void dobuleClick() = 0;
    virtual void click() = 0;
    virtual bool isLeaf() const { return true; }

    virtual void add(Component* c) {}
    virtual void remove(Component* c) {}
    virtual Component* remove(int index) {return nullptr;}
    virtual int getChildCount() const { return 0; }
    virtual Component* getChild(int index) const { return nullptr;}

    virtual string getName() const {
        return "Componet";
    }

    void describ(int ident=0) const {
        char identBuf[12];
        for(int i=0; i<ident && i<12;++i) {
            identBuf[i]='-';
        }
        identBuf[ident<12?ident:11]=0;

        fprintf(stdout, "%s name:%s\n", identBuf,getName().c_str());
        for(int i=getChildCount()-1; i>=0; --i) {
            Component* c = getChild(i);
            assert(c);
            c->describ(ident+1);
        }
    }
};

class Leaf : public Component {
public:
    void dobuleClick() override { fprintf(stdout, "Leaf::dobuleClick\n"); }
    void click() override { fprintf(stdout, "Leaf::click()\n"); }
    string getName() const override { return "Leaf"; }
};

NEWLEAF(LeafA);
NEWLEAF(LeafB);
NEWLEAF(LeafC);
NEWLEAF(LeafD);

class Composite : public Component {
public:
    virtual ~Composite() {
        for(int i=getChildCount()-1; i>=0; --i) {
            if(Component *c = getChild(i)) {
                delete c;
            }
        }
    }

    bool isLeaf() const override { return false;}

    void dobuleClick() override { fprintf(stdout, "Composite::dobuleClick()\n"); }
    void click() override { fprintf(stdout, "Composite::click()\n"); }
    void add(Component* c) {
        if(!c) return ;
        if(c == const_cast<Composite*>(this)) {
            /*!不允许加入自身*/
            assert(false);
            return ;
        }

        auto it = find(m_child.begin(), m_child.end(), c);
        if(it != m_child.end()) {
            /*!不允许已经存在的继续加入*/
            assert(false);
            return;
        }

        m_child.push_back(c);
    }

    int getChildCount() const override { return m_child.size(); }
    Component* getChild(int index) const override { if(index < 0 || index>=m_child.size()) return nullptr; return m_child[index];}
    void remove(Component* c) override { 
        if(!c) return ;
        auto it = find(m_child.begin(), m_child.end(), c);
        m_child.erase(it);
    }
    Component* remove(int index) {
        if(index < 0 || index >= m_child.size())
            return nullptr;
        auto i = m_child.begin() + index;
        auto r = *i;
        m_child.erase(i);
        return r;
    }
    string getName() const override { return "Composite";}
private:
    vector<Component*> m_child;
};

int main() {
    shared_ptr<Component> spc(new Composite);
    spc->add(new LeafA);
    spc->add(new LeafB);
    spc->add(new LeafC);
    spc->add(new LeafD);
    spc->add(new Leaf);

    Component* spc2{new Composite};
    spc2->add(new LeafA);
    spc2->add(new LeafB);
    spc2->add(new LeafC);
    spc->add(spc2);

    spc->describ();
    spc = nullptr;

    return 0;
}




 
