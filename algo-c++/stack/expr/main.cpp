#include <iostream>
#include <string>
#include <stack>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <cmath>

/*!
 * 1.为了保证最后进行清栈，最后一个入栈符号需要
 * 比其他的符号的优先级都要低,'\0'
 * 2.构建符号表
 * 3.需要两个堆栈，一个存储操作符，一个存储操作数
 * 4.默认都是右操作符
 * 5.左括号的优先级比其他任何符号的优先级都低，可以让其他符号入栈
 * 6.支持的符号
 * % (+,-) (*,/) (^, !)，(( )) 其中!是单目运算符,
*/

using namespace std;

#define NSYM (10)
enum Operator {
    END  , //'\0'
    ParenL,
    ParentR,
    Mod,
    Addition,
    Minus,
    Multipy,
    Divide,
    Pow,
    Fac,
    InvalidOper,
};

//栈顶操作符和当前操作符的比较, >表示出栈 ，<表示入栈,(水平方向)
//=表示特殊操作符, ' ' 表示不可能的操作
static char symtbl[NSYM][NSYM] = {
                        /*! END ParentL ParentR Mod Addition  Minus   Multipy Divide Pow Fac */
    /*! END */        '=' ,      '<',          ' ',        '<',     '<',              '<',         '<',          '<',        '<',    '<',
/*! ParenL */      ' ' ,     '>',              '=',        '<',     '<',              '<',         '<',          '<',        '<',    '<',
/*! ParentR*/     ' ' ,      ' ',               ' ',         ' ',     ' ',                 ' ',         ' ',            ' ',          ' ',    ' ',      /*! ParentR不可能入栈 */
    /*! Mod */       '>',     '<',              '>',        '>',     '<',              '<',         '<',          '<',        '<',    '<',
/*! Addition*/    '>',     '<',              '>',        '>',     '>',              '>',         '<',          '<',        '<',    '<',
    /*! Minus*/     '>',     '<',              '>',        '>',     '>',              '>',         '<',          '<',        '<',    '<',
/*! Multipy*/      '>',     '<',              '>',        '>',     '>',              '>',         '>',          '>',        '<',    '<',
/*! Divide*/        '>',     '<',              '>',        '>',     '>',              '>',         '>',          '>',        '<',    '<',
    /*! Pow*/        '>',     '<',              '>',        '>',     '>',              '>',         '>',          '>',        '>',    '<',
    /*! Fac*/          '>',     '<',              '>',        '>',     '>',              '>',         '>',          '>',        '>',    '>',
};

float readNumber(const char *&s) {
    char buf[16], *cp;
    int cnt=0;
    while(*s &&  (isdigit(*s) || *s == '.' )&& cnt < 15) buf[cnt++] = *(s++);
    buf[cnt] = 0;
    float f = strtof(buf, &cp);
    return f;
}

Operator sym2int(const char c) {
    switch(c) {
    case '+': return Addition;
    case '-':  return Minus;
    case '*': return Multipy;
    case '/': return Divide;
    case '!': return Fac;
    case '^': return Pow;
    case '(': return ParenL;
    case ')': return ParentR;
    case 0: return END;
    case '%': return Mod;
    }

    assert(false);
    return InvalidOper;
}

char operCmp(const char stackOper, const char oper) {
    Operator op1 = sym2int(stackOper), op2 = sym2int(oper);
    return symtbl[op1][op2];
}

float fac(float n) {
    if(n <= 0) return 1;
    long s = 1;
    for(long i = 2; i <= n; ++i)  s *= i;
    return s;
}

float calcu(float l, float r, Operator op) {
    switch(op) {
    case Mod:  return (int)l % (int)r;
    case Addition:  return l + r;
    case Minus : return l - r;
    case Multipy: return l * r;
    case Divide: return l / r ;
    case Fac: return fac(l);
    case Pow: return pow(l, r);
    default: return 0;
    }
    return 0;
}

float calcu(float l, float r, const char c) {
    return calcu(l, r, sym2int(c));
}

bool isUary(Operator op) {
    if(op == Fac) return true;
    return false;
}

bool isUary(const char c) {
    return isUary(sym2int(c));
}

int eval(const char *s) {
    stack<int> opt;
    stack<float> opn;
    if(!s || strlen(s) < 1) return 1;

    //这么做的目的是为了保证，栈上在计算的过程中
    //始终都可以抽出一个栈顶符号来参与运算
    opt.push(0);
    while(!opt.empty()) {
        if(isdigit(*s)) {
            opn.push(readNumber(s));
        } else {
            const char sopt = opt.top();
            switch(operCmp(sopt, *s)) {
            case '>': {
                //出栈,根据单目还是双目运算符来查看出栈的操作数
                float l ,r;
                r = opn.top(); opn.pop();
                if(!isUary(sopt)) {
                    l = opn.top(); opn.pop();
                } else {
                    l = r;
                    r = 0;
                }
                opn.push(calcu(l, r, sopt));
                opt.pop();
                break;
            }
            //针对pair型 END-END (-)
            case '=': {
                //不参与计算
                ++s;
                opt.pop();
                break;
            }
            case '<': {
                //直接入栈
                opt.push(*s);
                ++s;
                break;
            }
            default: { return 1;} //Error
            }
        }
    }

    cout<<"result="<<opn.top()<<endl;
    return 0;
}

void testStrtol() {
    const char *s1 = "32+",  *s2 = "45";
    char *cp1, *cp2;
    int n1 = strtol(s1, &cp1, 0);
    int n2 = strtol(s2, &cp2, 0);
    cout<<"n1="<<n1<<", n2="<<n2<<endl;
}

int main()
{
//    string s;
//    cin >> s;
    eval("3!+2!+5/2*(5-2)");
    eval("(0!+1)*2^(3!+4)-(5!-67-(8+9))");
    return 0;
}
