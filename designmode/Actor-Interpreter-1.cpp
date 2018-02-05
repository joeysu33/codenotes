/*!
 * 行为型设计模式-解释器
 * 样例程序，代码逻辑有点问题
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

/*!
 * Represents priority
 */
enum ExpressionType {
    ET_Assignment,
    ET_ConstVal,
    ET_Val,

    ET_Add,
    ET_Minus,
    ET_Multipy,
    ET_Divide,

    ET_Function,
    ET_LBracet,
    ET_RBracet,
    ET_None = 10000,
};

enum ValueType {
    VT_Int,
    VT_Var,
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
    IntValue(const IntValue& i): m_value(i.m_value) {}

    ValueType getType() const override{ return VT_Int; }
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

class VarIntValue : public IntValue {
public:
    explicit VarIntValue(const string& name, int value):
        m_name(name) ,IntValue(value) {}
    explicit VarIntValue(const char *name, int value) :IntValue(value){
        m_name = string(name);
    }

    ValueType getType() const override{ return VT_Var; }
    VarIntValue& operator=(const VarIntValue& vv) {
        this->m_name = vv.m_name;
        IntValue::operator=(vv);
    }

private:
    string m_name;
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
    string getName() const { return m_name; }
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
                fprintf(stdout, "####%s=%d",getName().c_str(), int(*iv));
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
    explicit ConstExpression(T* value):m_value(value) {}
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
    explicit VarExpression(const string& name, T* value = nullptr) :
        m_name(name), m_value(value) {}
    ~VarExpression() {
        if(m_value) delete m_value; 
    }
    T* getValue() const override{ return m_value; }
    void setValue(T* value) { m_value = value; }
    bool evaluate() override { return m_value; }
    ExpressionType getType() const override { return ET_Val; }
    string getName() const { return m_name; }
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
    class name : public Expression{ \
    public: \
        explicit name(Expression* op1, Expression* op2) \
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
                m_result = new IntValue(); \
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

    ~FunctionExpression() { if(m_result) delete m_result; }
    ExpressionType getType() const override { return ET_Function; }
    Value* getValue () const override { return m_result; }
    bool evaluate() override {
        if(m_name.empty()) return false;
        if(m_name == "add") {
            AddFunction f("add");
            assert(f.evaluate(m_arguments));
            m_result = new IntValue(*dynamic_cast<IntValue*>(f.getValue()));
        } else if(m_name== "print") {
            PrintFunction f("print");
            assert(f.evaluate(m_arguments));
            //m_result = new IntValue(*dynamic_cast<IntValue*>(f.getValue()));
            //no return value
        }
        return true;
    }
private:
    string m_name;
    list<Expression*> m_arguments;
    IntValue *m_result {nullptr};
};

class AssignmentExpression : public Expression {
public:
    /*!
     * expr1 左值 expr2 右值
     * expr1 = expr2
     */
    explicit AssignmentExpression(Expression *expr1, Expression* expr2) {
        m_expr1 = expr1;
        m_expr2 = expr2;
    }

    ExpressionType getType() const override { return ET_Assignment; }
    Value* getValue() const override {
        if(!m_expr1) return nullptr;
        return m_expr1->getValue();
    }

    bool evaluate() override {
        if(!m_expr1 || !m_expr2) return false;
        if(ConstIntExpression*e = dynamic_cast<ConstIntExpression*>(m_expr1)) {
            fprintf(stdout, "const value cant'be evaluated.\n");
            return false;
        }

            fprintf(stdout,"&&&&&&&&&&&&&&&&11\n");

        if(VarIntExpression* e = dynamic_cast<VarIntExpression*>(m_expr1) ){
            if(IntValue*i=dynamic_cast<IntValue*>(m_expr2->getValue())) {
                fprintf(stdout,"&&&&&&&&&&&&&&&&\n");
                e->setValue(new IntValue(*i));
            }
        }
        /*
        if(VarIntExpression* e = dynamic_cast<VarIntExpression*>(m_expr1) ){
            switch(m_expr2->getType()) {
                case ET_ConstVal:{
                                     if(ConstIntExpression* i=dynamic_cast<ConstIntExpression*>(m_expr2)){
                                             e->setValue(new IntValue(*i->getValue()));
                                     }
                                     break;
                                 }
                case ET_Val: {
                                 if(VarIntExpression *i = dynamic_cast<VarIntExpression*>(m_expr2)) {
                                     e->setValue(new IntValue(*i->getValue()));
                                 }
                                 break;
                             }
            }
        }
        */
        return true;
    }
private:
    Expression *m_expr1 {nullptr}, *m_expr2{nullptr};
};

class Parser {
public:
    ~Parser() { clear(); }
    explicit Parser(const string& file) { m_file = file; }
    bool parse() ;
private:
    void push(ExpressionType t);
    void clear();
    void process(ExpressionType t);
    void execute();
private:
    string m_file;
    stack<ExpressionType> m_stkExpr;
    stack<Expression*> m_values;
};

void Parser::clear() {
    while(!m_stkExpr.empty()) {
        m_stkExpr.pop();
    }
    while(!m_values.empty()) {
        delete m_values.top();
        m_values.pop();
    }
}

void Parser::process(ExpressionType t) {
    fprintf(stdout, "---------->process %d.\n",t);
    switch(t) {
        case ET_Assignment: {
                                assert(m_values.size() >= 2);
                                auto r=m_values.top();
                                m_values.pop();
                                auto l=m_values.top();
                                m_values.pop();
                                m_values.push(new AssignmentExpression(l,r));
                                m_values.top()->evaluate();
                                break;
                            }
        case ET_Add: 
        case ET_Minus:
        case ET_Multipy:
        case ET_Divide: {
                            assert(m_values.size() >= 2);
                            auto r=m_values.top();
                            m_values.pop();
                            auto l=m_values.top();
                            m_values.pop();
                            Expression *e {nullptr};
                            switch(t) {
                                case ET_Add: e=new OpAddIntExpr(l, r); break;
                                case ET_Minus: e=new OpMinusExpr(l,r); break;
                                case ET_Multipy: e=new OpMultipyExpr(l,r);break;
                                case ET_Divide: e= new OpDivideExpr(l,r); break;
                            }
                            m_values.push(e);
                            m_values.top()->evaluate();
                            break;
                        }
        case ET_Function: {
                              int n=0;
                              string name;
                              assert(m_values.size() >= 2);
                              if(VarIntExpression *e= dynamic_cast<VarIntExpression*>(m_values.top())) {
                                  name=e->getName();
                              } else { 
                                  fprintf(stdout,"debug:value_type:%d\n",m_values.top()->getType());
                                  assert (false); 
                              }
                              delete m_values.top();
                              m_values.pop();

                              if(ConstIntExpression* num= dynamic_cast<ConstIntExpression*>(m_values.top())) {
                                  n=dynamic_cast<IntValue*>(num->getValue())->getValue();
                              } else {
                                  assert(false);
                              }
                              delete m_values.top();
                              m_values.pop();

                              list<Expression*> args;
                              while(n--) {
                                  args.push_front(m_values.top());
                                  m_values.pop();
                              }
                              m_values.push(new FunctionExpression(name,args));
                              m_values.top()->evaluate();

                              break;
                          }
        case ET_RBracet: {
                             while(m_stkExpr.top() != ET_LBracet) {
                                 ExpressionType ii=m_stkExpr.top();
                                 m_stkExpr.pop();
                                 process(ii);
                             }
                             break;
                         }
    }
}

void Parser::push(ExpressionType t) {
    ExpressionType i=ET_None;
    while(!m_stkExpr.empty()) {
        i=m_stkExpr.top();
        if(i > t) {
            //reduce
            m_stkExpr.pop();
            process(i); 

        } else { break; }
    }
    fprintf(stdout, "===>push %d\n", t);
    m_stkExpr.push(t);
}

/*
 * void Parser::reduceToLBracet() {
    while(m_stkExpr.top() != ET_LBracet) {
    }

    m_stkExpr.pop();
}
*/

bool Parser::parse() {
    fstream f;
    f.open(m_file, fstream::in);
    if(f.fail()) return false;

    string func;
    char c{0}, n{0};
    int line {0}, row {0}, v{0}, cv{0}, argument{0};
    bool comment {false}, isFunc {false};
    char var[16];
    char constval[16];

    clear();
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
            /*!new line, execute line stence*/
            case '\n':{
                          line++; 
                          row=0;
                          
                          break;
                      }
            case 'a':case 'b':case'c':case'd':case 'e':case 'f':case 'g': case 'h': case 'i':
            case 'j': case 'k': case 'l': case 'm':case 'n': case 'o': case 'p': case 'q':
            case 'r': case 's': case 't': case 'u': case 'v': case 'w':
            case 'x':
            case 'y':
            case 'z':
                      {
                          if(v >= 15) assert(false);
                          var[v++]=c;
                          if(n == '(') {
                              var[v]=0;
                              v=0;
                              argument=0;
                              isFunc=true;
                              func=string(var);
                              fprintf(stdout, "func-name:%s.\n", var);
                          }
                          /*!
                           * single alpha as var-name
                           */
                          else if(!isalpha(n) ) {
                              /*! it's the end of the var*/
                              var[v]=0;
                              v=0;
                              if(isFunc) argument++;
                              m_values.push(new VarIntExpression(string(var),new IntValue(-9999)));
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
                                                          m_values.push(new ConstIntExpression(new IntValue(atoi(constval))));
                                                          if(isFunc) argument++;
                                                          fprintf(stdout, "constval=%s.\n",constval);
                                                      }
                                                      break;
                                                  }
            case '+':
            case '-':
            case '*':
            case '/': {
                          fprintf(stdout, "op:%c.\n",c);
                          switch(c) {
                              case '+': push(ET_Add); break;
                              case '-': push(ET_Minus); break;
                              case '*': push(ET_Multipy); break;
                              case '/': push(ET_Divide); break;
                          }
                          break;
                      }
            case '=': {
                          fprintf(stdout, "assign:%c.\n",c);
                          push(ET_Assignment);
                          break;
                      }
            case ',': {
                          break;
                      }
            case '(':
                      {
                          fprintf(stdout, "(");
                          push(ET_LBracet);
                          break;
                      }
            case ')': {
                          fprintf(stdout,")");
                          if(isFunc) {
                              assert(m_stkExpr.top() == ET_LBracet);
                              m_stkExpr.pop(); //不允许函数中包含'('或')'
                              isFunc=false;
                              /*! 参数个数入栈*/
                              m_values.push(new ConstIntExpression(new IntValue(argument)));
                              /*!函数名称*/
                              m_values.push(new VarIntExpression(func));
                              push(ET_Function);
                          } else {
                              m_stkExpr.push(ET_RBracet);
                          }
                          break;
                      }
        }
    }

    execute();
    fprintf(stdout, "code lines:%d.\n",line);
    f.close();
    return true;
}

void Parser::execute() {
    while(!m_stkExpr.empty()) {
        auto t=m_stkExpr.top();
        m_stkExpr.pop();
        process(t);
    }
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


