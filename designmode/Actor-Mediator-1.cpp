/*!
 * 设计模式 行为类-中介者模式
 * 角色
 * 1.中介者
 * 2.同事
 * 流程
 * 同事之间的交流通过中介者，同事给中介传送消息
 * 消息到达中介之后，中介将消息传送给其他同事,
 * 或者直接处理该请求。
 * 举例: （租房中介)
 * 1.房主(触发消息通知的起点)通过中介将房屋的信息挂到中介所，租房者根据自己对房屋状况
 * 和价格在中介所留下信息(订阅)，如果存在合适的，则中介将其推荐给租房者(通知)
 * (同事之间通过OA办公)
 * 2.各个同事之间的关系均是等价的,同事A可以将某些信息传递给同事B或C，同事B也可以提醒A
 * 做某些工作，同事C也可以约其他人一起吃完饭
 * 特点：
 * 中介模式和观察者模式的区别
 * 1.触发对象不同，中介模式中，消息的传播不一定是直接由中介完成（可以是由房东完成）。
 *   而观察着模式的消息通知一定是通过被观察者完成。
 */

/*!
 * 以OV系统作为中介来配合办公室的
 * 同事进行办公
 * IOA: OA系统的接口类
 * College: 同事（员工,包含老板)
 * 解耦同事之间直接进行操作
 * 在College上聚合一个IOA
 *
*/

/*!
 * 在编写代码中的几个问题
 * 1.union结构重复释放,union合并使用一份内存
 * 2.因为在Colleage的析构函数中会一并解耦OASys，所以在OASys中delete一个College的时候
 *   一定会调用remove，这个时候如果引用head头指针可能会有问题
 * 3.双向链表写的时候要考虑next指针为空的情况，next为空则next的prev指针没法赋值
 * 4.字符串拷贝要仔细，光分配内存忘记拷贝了
 */

#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string.h>

using namespace std;

enum Operator {
    OP_None,
    OP_Mail,
    OP_Notify,
    /*! 需要command特权*/
    OP_Command,
};

enum Status {
    S_OK,
    S_RecvNotOnline,
    S_ErrorMsg,
    S_LowPriority,
};

#define COMMAND_PRIORITY 10

struct Data {
    ~Data() { if(m_d) delete []m_d; }
    char *m_d {nullptr};
    int m_size {0};
};

struct Message {
    Message() {m_words=nullptr; m_data=nullptr;}
    ~Message() { 
        /*! m_words和m_data使用同一份内存，不能释放两次*/
        if(m_type == OP_None) return ;
        if(m_type != OP_Mail)
            if(m_words) delete []m_words;
        else
            if(m_data) delete m_data;
    }

    string m_from;
    Operator m_type {OP_None};
    /*!
     * union can't initialized by c++11
     * union XX {
     *  //错误写法
     *  char *m_words {nullptr}; XXXXXX
     * }
     */
    //无名union，直接使用
    union {
        char *m_words ;
        Data *m_data ;
    };
};

class College;
class IOA {
public:
    virtual ~IOA() {}
    virtual int sendMessage(College *c, Message *msg) = 0;
    virtual int sendMessage(const string& name, Message *msg) = 0;
    virtual void add(College *c) = 0;
    virtual void remove(College *c) = 0;
    virtual void status() const = 0;
    virtual College* find(const string& name) const= 0;
};

class College {
public:
    College(IOA* oa, const string& name = string()) :m_name(name),m_oa(oa){ assert(oa); m_oa->add(this); printf("%s online.\n", getName().c_str());}
    ~College() {
        m_oa->remove(this);
        printf("%s offline.\n", getName().c_str());
    }

    string getName() const { return m_name; }
    void setName(const string& name) { m_name = name; }

    int command(const char *name, const char *words)  {
        return command(m_oa->find(name), words);
    }

    virtual int command(College *c, const char *words)  {
        if(!m_oa || !c || !words) return S_ErrorMsg;
        Message *msg = new Message();
        msg->m_type = OP_Command;
        msg->m_words = duplicate(words);
        msg->m_from = m_name;
        return m_oa->sendMessage(c, msg);
    }

    int notify(const char *name, const char *words) {
        return notify(m_oa->find(name), words);
    }

    virtual int notify(College *c, const char *words) {
        if(!m_oa || !c || !words) return S_ErrorMsg;
        Message *msg = new Message();
        msg->m_type = OP_Notify;
        msg->m_words = duplicate(words);
        msg->m_from = m_name;
        return m_oa->sendMessage(c, msg);
    }

    int sendEmail(const char *name, const char *mail)  {
        return sendEmail(m_oa->find(name), mail);
    }

    virtual int sendEmail(College *c, const char *mail)  {
        if(!m_oa || !c || !mail) return S_ErrorMsg;
        Message *msg = new Message();
        msg->m_type = OP_Mail;
        msg->m_data = new Data();
        msg->m_data->m_d = duplicate(mail);
        msg->m_data->m_size = strlen(mail);
        msg->m_from = m_name;
        return m_oa->sendMessage(c, msg);
    }

protected:
    virtual int priority() const { return 1; }
private:
    char *duplicate(const char *s) const {
        int n=strlen(s);
        char *s1 = new char[n+1], *s2=s1;
        /*!注意事项,拷贝字符串终止符'/0'*/
        while((n--)>=0) *(s2+n)=*(s+n);
        return s1;
    }
    virtual int receive(Message *msg) {
        string type, content;
        switch(msg->m_type) {
            case OP_Command: {
                                 type="Command";
                                 content=msg->m_words;
                                 break;
                             }
            case OP_Notify: {
                                type="Notify";
                                content=msg->m_words;
                                break;
                            }
            case OP_Mail: {
                              type="Email";
                              content=msg->m_data->m_d;
                              break;
                          }
            default: {
                         type="Unknown";
                         content="<None>";
                         break;
                     }
        }
        printf("msg from:%s,msg to:%s, content:%s type:%s\n",
                msg->m_from.c_str(), m_name.c_str(),content.c_str(), type.c_str());
    }
    friend class OASys;
private:
    IOA *m_oa {nullptr};
    string m_name;
};

class OASys : public IOA{
private:
    struct Node {
        Node(College* c) :m_c(c) {}
        ~Node() { if(m_c) delete m_c; }
        College *m_c {nullptr};
        Node *m_next {nullptr};
        Node *m_prev {nullptr};
    };
public:
    OASys() { m_head = new Node(nullptr);  printf("OASys start!\n");}
    virtual ~OASys() { 
        /*!特别注意，首先释放Node,最后释放head
         * 因为释放Node会导致调用remove，而head不在remove中
         * 会把head直接置空
         */
        Node* t=m_head->m_next, *t1=t;
        while(t) {
            t1=t;
            t=t->m_next;
            /*!需要考虑delete和new的隐含调用规则*/
            delete t1;
        }
        delete m_head;
        printf("OASys shutdown!\n");
    }
    virtual College* find(const string& name) const override{
        Node* t{m_head->m_next};
        while(t) {
            if(t->m_c->getName() == name) return t->m_c;
            t=t->m_next;
        }
        return nullptr;
    }

    virtual int sendMessage(College *c, Message *msg) override {
        if(!c || !msg) {
            return S_ErrorMsg;
        }

        int n=c->receive(msg);
        delete msg;
        return n;
    }

    virtual int sendMessage(const string& name, Message *msg) {
        if(College *c = find(name)) {
            return sendMessage(c, msg);
        }

        printf("Not this person online, named:%s", name.c_str());
        return S_RecvNotOnline;
    }

    virtual void add(College *c) override {
        if(!c) return ;
        Node *t{m_head};
        while(t->m_next) {
            t=t->m_next;
        }
        t->m_next=new Node(c);
        t->m_next->m_prev = t;
    }

    /*!remove不释放内存*/
    virtual void remove(College *c) override {
        if(!c) return ;
        Node *t{m_head->m_next};
        while(t) {
            if(t->m_c == c) {
                t->m_prev->m_next=t->m_next;
                /*!需要考虑t->m_next为空的情况*/
                if(t->m_next)
                    t->m_next->m_prev=t->m_prev;
                break;
            }
            t = t->m_next;
        }
    }

    void status() const override {
        printf("size=%d\n", size());
        Node *t{m_head->m_next};
        while(t) {
            printf("%s,",t->m_c->getName().c_str());
            t=t->m_next;
        }
        printf("\n");
    }

private:
    int size() const {
        int n1=0, n2=0;
        Node* t{m_head->m_next}, *tp=nullptr;
        while(t) {
            ++n1;
            tp=t;
            t=t->m_next;
            assert(tp->m_next==t);
            if(t) assert(t->m_prev == tp);
        }

        while(tp) {
            n2++;
            tp=tp->m_prev;
        }
        n2--;

        assert(n1==n2);
        return n1;
    }
private:
    Node *m_head;
};

class Boss : public College{
public:
    Boss(IOA *oa, const string& name = string()) :College(oa, name) {}
protected:
    virtual int priority() const { return 11; }
};

int main() {
    IOA *oa = new OASys();
    College *a1 = new College(oa,"a1");
    College *a2 = new College(oa,"a2");
    College *a3 = new College(oa,"a3");
    College *a4 = new College(oa,"a4");
    College *boss = new College(oa, "boss");
    
    oa->status();
    a1->command("a2","to cleanup");
    boss->command("a1", "to cleanup");
    boss->command("a8", "to cleanup");
    a2->notify("a3", "to have dinner");
    a4->sendEmail("a1", "happy birthday!!!");

    delete boss;
    //delete a4; delete a3; delete a2; delete a1;
    oa->status();
    delete oa;
    return 0;
}



