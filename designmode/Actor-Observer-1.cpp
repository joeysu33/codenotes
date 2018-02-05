/*!
 * 设计模式-观察者(observer)
 * 角色
 * 1.被观察者
 * 2.观察者
 * 过程:被观察者的某些属性发生变化，发出通知，由
 * 观察者来做出相应的反应
 */
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory>

using namespace std;

/*!
 * Observer
 */
class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update() = 0;
};

class Observer1 : public IObserver {
public:
    virtual void update() override{
        cout<<"observer1:update()"<<endl;
    }
};

class Observer2: public IObserver {
public:
    virtual void update() override {
        cout<<"observer2:update()"<<endl;
    }
};

typedef shared_ptr<IObserver> ObserverSP;

/*!
 *Observered
 */
class Subject{
public:
    virtual ~Subject() {}
    void attach(const ObserverSP &o) { 
        if(!o) return ;
        auto i=find(m_observers.begin(), m_observers.end(), o);
        if(i != m_observers.end()) return ;

        m_observers.push_back(o);
    }

    void detach(const ObserverSP& o) {
        if(!o) return ;
        auto i=find(m_observers.begin(), m_observers.end(), o);
        if(i == m_observers.end()) return ;
        m_observers.erase(i);
    }

    void notify() {
        for(ObserverSP & o: m_observers) {
            if(o)
                o->update();
        }
    }
protected:
    vector<ObserverSP> m_observers;
};


int main() {
    ObserverSP osp1(new Observer1), osp2(new Observer2);
    Subject subject;
    subject.attach(osp1); subject.attach(osp2);
    subject.notify();

    return 0;
}


