/*!
 * 设计模式 - 职责链
 * 很类似与Qt中的事件处理
 * Qt在事件处理的时候，如果触发某个事件，则事件消息会首先
 * 交由该对象进行处理，如果该对象返回true，则说明消息已经
 * 处理，不会继续传递，否则消息沿着派生线会一直交由基类来进行递归处理
 * 角色：
 * 1.触发职责对象
 * 2.职责链
 */

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cassert>

enum MsgType {
    MT_Click,
    MT_DClick,
    MT_Touch,
    MT_None,
};

struct Msg {
    MsgType m_type {MT_None};
    int m_data {0};
};

/*!
 * 窗口基类
 */
class Widget{
public:
    virtual ~Widget() {}
protected:
    virtual bool event(const Msg&msg) { return false; }
    friend class MessageDispatcher;
};

class Window : public Widget {
protected:
    bool event(const Msg &msg ) override{
        /*!
         * 关心这样的数据，进行处理
         */
        if(msg.m_type == MT_Click && msg.m_data == 100) {
            fprintf(stdout, "Window(MT_Click,100)\n");
            return true;
        }

        /*!
         * 不关系，交由其他想处理的人处理
         */
        return Widget::event(msg);
    }
};

class Button : public Window{
protected:
    bool event(const Msg& msg) override {
        if(msg.m_type == MT_DClick) {
            fprintf(stdout, "Button(MT_DClick)\n");
            return true;
        }

        /*!
         * Have more priority 
         */
        if(msg.m_type == MT_Click) {
            fprintf(stdout, "Button also click.\n");
            return false;
        }
        return Window::event(msg);
    }
};

/*!
 * 窗口消息分发
 */
class MessageDispatcher {
public:
    ~MessageDispatcher() {
        for(Widget *w : m_all) delete w;
    }
    bool dispatch(const Msg& msg) {
        if(m_widget) {
            if(m_widget->event(msg)) {
                return true;
            }
        }

        /*!
         * 尝试让其他人处理
         */
        for(Widget *w : m_all) {
            if(w == m_widget) continue;
            if(w->event(msg)) return true;
        }

        /*!
         * 没有任何人能处理这个消息
         */
        return false;
    }

    void setCurrentWindow(Widget* w) {
        if(!w) return ;
        auto i = std::find(m_all.begin(), m_all.end(), w);
        if(i==m_all.end()) 
            push_back(w);

        m_widget = w;
    }
    Widget* getCurrentWindow() const { return m_widget; }

    void push_back(const Widget* w) { 
        if(!w) return ;
        std::vector<Widget*>::iterator i;
        if((i = std::find(m_all.begin(), m_all.end(), w)) == m_all.end())
            m_all.push_back(const_cast<Widget*>(w)); 
    }
    Widget* pop_back()  { Widget *r {m_all.back()}; m_all.pop_back(); return r; }
private:
    Widget *m_widget {nullptr};
    std::vector<Widget*> m_all;
};

int main() {
    Msg msg;
    MessageDispatcher md;
    Window *w1 = new Window();
    Button *b1 = new Button();
    md.push_back(w1);
    md.push_back(b1);
    md.setCurrentWindow(b1);

    msg.m_type = MT_Click;
    msg.m_data = 100;
    md.dispatch(msg);

    msg.m_type = MT_DClick;
    md.dispatch(msg);

    return 0;
}




