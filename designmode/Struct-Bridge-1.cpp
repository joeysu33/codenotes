/*!
 * 设计模式-结构型-桥接(Bridge)
 * 和Pimpl的设计思路一致
 * 角色
 * 1.外部接口类
 * 2.内部实现类
 */

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

class WindowImpl {
public:
    virtual ~WindowImpl() {}
    virtual void doDrawText() = 0;
    virtual void doDrawRect() = 0;
};

class IconWindowImpl : public WindowImpl {
public:
    void doDrawText() override { fprintf(stdout, "IconWindowImpl::doDrawText()\n"); }
    void doDrawRect() override { fprintf(stdout, "IconWindowImpl::doDrawRect()\n"); }
};

class Window {
public:
    virtual ~Window() {
        if(m_impl == nullptr) {
            delete m_impl;
        }
    }
    virtual void drawText() = 0;
    virtual void drawRect() = 0;
    virtual WindowImpl* getImpl() const { return m_impl;}
protected:
    WindowImpl* m_impl {nullptr};
};

class IconWindow : public Window {
public:
    virtual ~IconWindow() {}
    IconWindow() { m_impl = new IconWindowImpl(); }
    void drawText() override { m_impl->doDrawText(); }
    void drawRect() override { m_impl->doDrawRect(); }
};

int main() {
    IconWindow iw;
    iw.drawText();
    iw.drawRect();

    return 0;
}
