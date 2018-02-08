/*!
 * 设计模式-模板方法(Template Method)
 * 角色
 * 1.Abstract Class
 * 2.Concrete Class
 *
 */

#include <string>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <memory>

using namespace std;

class IDocument {
public:
    virtual ~IDocument() {}
    virtual void open() = 0;
    virtual void save() const = 0;
    virtual void close() = 0;
};

class MyDoc1 : public IDocument {
public:
    void open() override{
        cout<<"MyDoc1::open()"<<endl;
    }

    void save() const override {
        cout<<"MyDoc1::save()"<<endl;
    }

    void close() override {
        cout<<"MyDoc1::close()"<<endl;
    }
};

class MyDoc2 : public IDocument {
public:
    void open() override {
        cout<<"MyDoc2::open()"<<endl;
    }

    void save() const override {
        cout<<"MyDoc2::save()"<<endl;
    }

    void close() override {
        cout<<"MyDoc2::close()"<<endl;
    }
};

typedef shared_ptr<IDocument> DocumentSP;
class IApplication {
public:
    virtual ~IApplication() {}
    void openDocument() {
        if(!m_doc) return ;
        if(!canOpenDocument()) return ;
        doOpenDocument();
    }

    void closeDocument() {
        if(!m_doc) return ;
        m_doc->close();
    }

    void saveDocument() const {
        if(!m_doc) return ;
        m_doc->save();
    }

    DocumentSP getDoc() const { return m_doc; }
    void setDoc(const DocumentSP& doc) { m_doc = doc; }
protected:
    virtual void doOpenDocument() {
        if(m_doc) m_doc->open();
    }
    virtual bool canOpenDocument() const = 0;
private:
    DocumentSP m_doc;
};

class MyApp1 : public IApplication {
public:
    MyApp1() {}
protected:
    void doOpenDocument() {
        cout<<"openDocument by MyApp1"<<endl;
    }

    bool canOpenDocument() const override{
        return true;
    }
};

class MyApp2 : public IApplication {
public:
    MyApp2() {}
protected:
    void doOpenDocument() {
        cout<<"openDocument by MyApp2"<<endl;
    }

    bool canOpenDocument() const override{
        return true;
    }
};

int main() {
    MyApp1 ma1;
    MyApp2 ma2;
    ma1.setDoc(DocumentSP(new MyDoc1));
    ma2.setDoc(DocumentSP(new MyDoc2));
    ma1.openDocument();
    ma1.closeDocument();

    ma2.openDocument();
    ma2.closeDocument();

    return 0;
}


