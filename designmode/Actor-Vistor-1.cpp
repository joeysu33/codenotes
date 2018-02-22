/*!
 * 访问者模式 (Visitor)
 * 角色:
 * 1.Visitor,为对象结构中每一个ConcreteElement声明一个visitor操作
 * 2.ConcreteVisitor
 * 3.Element，定义一个accept操作，传递一个visitor参数
 * 4.ConcreteElement,实现一个accept操作，传递visitor参数
 * 给每个实体的元素实现一个访问方法
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

using namespace std;
class Animal;
class Pig;
class Dog;
class Cat;

class IVisitor {
public:
    virtual ~IVisitor() {}
    virtual void visitPig(Pig* a) = 0;
    virtual void visitDog(Dog* a) = 0;
    virtual void visitCat(Cat* a) = 0;
};

class Animal{
public:
    virtual ~Animal() {}
    virtual void accept(IVisitor* v) = 0;
};

class Pig : public Animal {
public:
    virtual void accept(IVisitor* v) {
        if(!v) return ;
        v->visitPig(this);
    }
};

class Dog : public Animal {
public:
    virtual void accept(IVisitor* v) {
        if(!v) return ;
        v->visitDog(this);
    }
};

class Cat : public Animal {
public:
    virtual void accept(IVisitor* v) {
        if(!v) return ;
        v->visitCat(this);
    }
};

class HelloVisitor : public IVisitor{
public:
    virtual void visitPig(Pig* a) override { cout<<"Hello pig"<<endl; }
    virtual void visitDog(Dog* a) override { cout<<"Hello dog"<<endl; }
    virtual void visitCat(Cat* a) override { cout<<"Hello cat"<<endl; }
};

class SoundVisitor : public IVisitor{
public:
    void visitPig(Pig* a) override { cout<<"mm..."<<endl; }
    void visitDog(Dog* a) override { cout<<"wow.."<<endl; }
    void visitCat(Cat* a) override { cout<<"mow.."<<endl; }
};

class FootPrintVisitor : public IVisitor {
public:
    void visitPig(Pig* a) override { cout<<"pig footprint"<<endl; }
    void visitDog(Dog* a) override { cout<<"dog footprint"<<endl; }
    void visitCat(Cat* a) override { cout<<"cat footprint"<<endl; }
};

using namespace std;

int main() {
    HelloVisitor hv;
    SoundVisitor sv;
    FootPrintVisitor fv;

    vector<Animal*> all {new Dog,new Pig, new Cat, new Cat, new Pig};
    for(Animal* a : all) a->accept(&hv);
    cout<<endl;

    for(Animal* a : all) a->accept(&sv);
    cout<<endl;

    for(Animal* a : all) a->accept(&fv);
    cout<<endl;

    for(Animal* a: all) delete a;
    return 0;
}




