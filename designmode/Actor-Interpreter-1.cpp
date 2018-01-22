/*!
 * 行为型设计模式-解释器
 * Interpreter
 */

#include <string>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <list>
#include <map>
#include <fstream>
#include <stack>

using namespace std;

namespace {
    static const char sc_comment_sym = '#';
}

enum ExpressionType {
    ET_ConstVal,
    ET_Val,
    ET_Add,
    ET_Minus,
    ET_Multipy,
    ET_Divide,
    ET_Function,
    ET_None = 10000,
};

enum ValueType {
    VT_Int,
};

class Value {
public:
    virtual ~Value() {}
    virtual ValueType getType() const = 0;
};

class IntValue : public Value{
public:
    explicit IntValue() :m_value(0) {}
    explicit IntValue(int t):m_value(t) {}
    ValueType getType() const { return VT_Int; }
    IntValue& operator=(const IntValue& other) {
        this->m_value = other.m_value;
        return *this;
    }
    int getValue() const { return m_value; }
    void setValue(int val) {m_value = val; }

    operator int() const{
        return m_value;
    }
private:
    int m_value {0};
};

//=======================================================
class Expression {
public:
    virtual ~Expression() { fprintf(stdout, "free expr address:0x%08x.\n", *(unsigned int*)this);}
    Expression() { fprintf(stdout, "new expr address:0x%08x.\n", *(unsigned int*)this); }

    /*! 为了简单，在此省略上下文 */
    //virtual bool evaluate(const Context& context) = 0;
    virtual bool evaluate() = 0;
    virtual ExpressionType getType() const = 0;
    virtual Value* getValue() const = 0;
};

//=======================================================
class Function {
public:
    explicit Function(const string& name):m_name(name) {}
    virtual ~Function() { if(m_value) delete m_value;}
    virtual bool evaluate(const list<Expression*>& expr) = 0;
    virtual Value* getValue() const { return m_value; }
protected:
    IntValue *m_value {nullptr};
private:
    string m_name;
};

class AddFunction : public Function{
public:
    explicit AddFunction(const string& name):Function(name) {}
    virtual bool evaluate(const list<Expression*>& expr) override{
        if(expr.empty()) return false;
        int ii {0};
        for(auto i=expr.begin(); i != expr.end(); ++i) {
            if(!(*i)) continue;
            if(IntValue* iv = dynamic_cast<IntValue*>((*i)->getValue())) {
                ii += *iv;
            }
        }

        if(!m_value) { 
            m_value = new IntValue(ii);
        }else {
            m_value->setValue(ii);
        }

        return true;
    }
};

class PrintFunction : public Function {
public:
    explicit PrintFunction(const string& name) : Function(name) {}
    virtual bool evaluate(const list<Expression*>& expr) override {
        if(expr.empty()) return false;
        for(auto i=expr.begin(); i!= expr.end(); ++i) {
            if(!(*i)) continue;
            if(IntValue* iv = dynamic_cast<IntValue*>((*i)->getValue())) {
                fprintf(stdout, "%d", int(*iv));
            }
        }
        return true;
    }
};

//=======================================================
/*!
 * 常量/变量运算因子
 */
template<class T>
class ConstExpression : public Expression{
public:
    explicit ConstExpression(const T& value):m_value(new T(value)) {}
    ~ConstExpression() {
        if(m_value) delete m_value;
    }
    T* getValue() const override{ return m_value; }
    bool evaluate () override { return m_value; }
    ExpressionType getType() const override { return ET_ConstVal; }
private:
    T *m_value {nullptr};
};

template<class T>
class VarExpression : public Expression{
public:
    explicit VarExpression(const string& name, const T& value = T()) :
        m_name(name), m_value(new T(value)) {}
    ~VarExpression() {
        if(m_value) delete m_value; 
    }
    T* getValue() const override{ return m_value; }
    void setValue(const T& value) { m_value = value; }
    bool evaluate() override { return m_value; }
    ExpressionType getType() const override { return ET_Val; }
private:
    string m_name;
    T *m_value {nullptr};
};

typedef ConstExpression<IntValue> ConstIntExpression;
typedef VarExpression<IntValue> VarIntExpression;

/*!
 * 运算操作
 */
#define OpExpression(name,op,exprtype) \
    template<class T> \
    class name : public Expression{ \
    public: \
        explicit name(const Expression* op1, const Expression* op2) \
            :m_op1(op1), m_op2(op2){ \
            } \
        ~ name() { \
            if(m_result) delete m_result; \
            if(m_op1) delete m_op1; \
            if(m_op2) delete m_op2; \
        } \
        bool evaluate() override { \
            if(!m_op1 || !m_op2) return false; \
            if(!m_result) { \
                m_result = new T(); \
            }\
            IntValue *i1 = dynamic_cast<IntValue*>(m_op1); \
            IntValue *i2 = dynamic_cast<IntValue*>(m_op2); \
            if(!i1 || !i2) return false; \
            m_result->setValue(i1->getValue() op i2->getValue()); \
            return true; \
        }\
        ExpressionType getType() const override { return exprtype; } \
        Value* getValue() const override { \
            return m_result; \
        }\
    private: \
        Expression *m_op1 {nullptr}, *m_op2 {nullptr}; \
        /*! expression result */ \
        IntValue *m_result {nullptr};\
    };

OpExpression(OpAddIntExpr,+,ET_Add) ;
OpExpression(OpMinusExpr,-,ET_Minus);
OpExpression(OpMultipyExpr,*,ET_Multipy);
OpExpression(OpDivideExpr,/,ET_Divide);

class FunctionExpression : public Expression {
public:
    explicit FunctionExpression(const string& name, const list<Expression*>& arguments) {
        m_name = name;
        m_arguments = arguments;
    }

    ExpressionType getType() const override { return ET_Function; }
    Value* getValue () const override { return m_result; }
    bool evaluate() override {
        if(m_name.empty()) return false;
        return true;
    }
private:
    string m_name;
    list<Expression*> m_arguments;
    IntValue *m_result {nullptr};
};

class Parser {
public:
    explicit Parser(const string& file) { m_file = file; }
    bool parse() ;
private:
    string m_file;
};

bool Parser::parse() {
    fstream f;
    f.open(m_file, fstream::in);
    if(f.fail()) return false;

    char c{0}, n{0};
    int line {0}, row {0}, v{0}, cv{0};
    bool comment {false};
    char var[16];
    char constval[16];
    stack<Expression*> stk;
    stack<Value*> val;

    while(f.get(c)) {
nextline:
        if(comment) {
            if(c !='\n') 
                continue;
            else {
                comment = false;
            }
        }

        n=f.peek();
        switch(c) {
            /*!ignore symbols */
            case ' ':  break;
            case '\t': break;
            case '#': {
                          if(row==0) {
                              comment = true;
                              goto nextline;
                          }
                          break;
                      }
            /*!new line*/
            case '\n':line++; row=0;break;
            case 'a':case 'b':case'c':case'd':case 'e':case 'f':case 'g': case 'h': case 'i':
            case 'j': case 'k': case 'l': case 'm':case 'n': case 'o': case 'p': case 'q':
            case 'r': case 's': case 't': case 'u': case 'v': case 'w':
            case 'x':
            case 'y':
            case 'z':
                      {
                          if(v >= 15) assert(false);
                          var[v++]=c;
                          if(c == '(') {
                              var[v]=0;
                              v=0;
                              fprintf(stdout, "func-name:%s.\n", var);
                          }
                          else if(!isalpha(n) && !isdigit(n)) {
                              /*! it's the end of the var*/
                              var[v]=0;
                              v=0;
                              fprintf(stdout, "var-name:%s.\n", var);
                          }
                          break;
                      }
            case '0':case '1':case '2': case '3': case '4': case '5':
            case '6':case '7':case '8': case '9': {
                                                      if(cv >= 15) assert(false);
                                                      constval[cv++]=c;
                                                      if(!isdigit(n)) {
                                                          constval[cv]=0;
                                                          cv=0;
                                                          val.push(new IntValue(atoi(constval)));
                                                          fprintf(stdout, "constval=%s.\n",constval);
                                                      }
                                                      break;
                                                  }
            case '+':
            case '-':
            case '*':
            case '/': {
                          fprintf(stdout, "op:%c.\n",c);
                          break;
                      }
            case '=': {
                          fprintf(stdout, "assign:%c.\n",c);
                          break;
                      }
            case '(':
                      {
                          fprintf(stdout, "(");
                          break;
                      }
            case ')': {
                          fprintf(stdout,")");
                          break;
                      }
        }
    }

    fprintf(stdout, "code lines:%d.\n",line);
    f.close();
    return true;
}


int main() {
    int i{10};
loop1:
    while(i>=0) {
        printf("%d,", i--);
    }
    printf("\n");
    Parser p("hello.script");
    assert(p.parse());


    return 0;
}


