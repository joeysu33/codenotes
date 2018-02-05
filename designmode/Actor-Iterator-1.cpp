/*!
 * 设计模式-行为（迭代器)
 * 别名:Cursor
 */
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <initializer_list>

using namespace std;
typedef struct _Node {
    _Node(int n):m_data(n) {}
    _Node() {}

    int m_data {0};
    _Node* m_next {nullptr};
}Node, *PNode;

class List;
class ListIterator {
public:
    /*! ++i operator++*/
    ListIterator operator++() {
        assert(m_list);
        m_list=m_list->m_next;
        return *this;
    }
    
    /*! i++ operator++*/
    ListIterator operator++(int) {
        assert(m_list);
        ListIterator t(m_list);
        m_list=m_list->m_next;
        return t;
    }

    int operator*() const{
        if(!m_list) assert(false);
        return m_list->m_data;
    }

    const Node* operator->() const{
        return m_list;
    }

    Node* operator->() {
        return m_list;
    }

    bool operator==(const ListIterator& other) {
        if(m_list == other.m_list) return true;
        return false;
    }

    bool operator!=(const ListIterator& other) {
        return !operator==(other);
    }

    ListIterator& operator=(const ListIterator& other) {
        m_list=other.m_list;
        return *this;
    }

private:
    ListIterator(Node* node) :m_list(node) {}
    ListIterator() {}
    friend class List;
private:
    Node *m_list {nullptr};
};

class List{
public:
    List() { m_head = new Node();}
    List(const initializer_list<int>& i) {
        m_head =new Node(); 
        for(auto ii : i) {
            operator<<(ii);
        }
    }

    ~List() {
        Node *t;
        while(m_head) {
            t=m_head;
            m_head = m_head->m_next;
            delete t;
        }
    }

    ListIterator begin() { return ListIterator(m_head->m_next); }
    const ListIterator cbegin() const { return ListIterator(m_head->m_next); }
    ListIterator end() { return ListIterator(); }
    const ListIterator cend() const { return ListIterator(); }
    bool empty() const { return !m_head->m_next; }
    List& operator<<(const int val) {
        Node *t=m_head;
        while(t->m_next) {
            t= t->m_next;
        }
        t->m_next=new Node(val);
        return *this;
    }
    unsigned size() const {
        int n{0};
        Node *t {m_head};
        while(t->m_next) {
            n++;
            t=t->m_next;
        }
        return n;
    }
    void show() const {
        printf("elements count:%d\n", size());
        for(auto i=cbegin(); i != cend(); ++i) {
            printf("%d,",*i);
        }
        printf("\n");
    }
private:
    /*! head pointer*/
    Node *m_head;
};

int main() {
    List list, list2 {10,30,40,100,80};
    list<<10<<20<<50<<100<<1000;
    list.show();
    list2.show();

    return 0;
}
