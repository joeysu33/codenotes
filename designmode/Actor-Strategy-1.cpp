/*!
 * 设计模式-策略模式(Strategy | Policy)
 * 角色:
 * 1.Strategy 策略(定义算法的公共接口)
 * 2.Concrete Strategy 具体策略(具体的算法)
 * 3.Context 上下文（在上下文中聚合一个策略基类对象)
 * 流程：
 * 在Context(上下文）中维护一个Strategy(策略），Context中
 * 来执行Strategy的某些接口
 */

#include <iostream>
#include <string>
#include <cstdio>
#include <memory>

using namespace std;
/*!
 * 二元参数算法接口
 */
class IBinaryAlgorithm {
public:
    IBinaryAlgorithm() { cout<<"IBinaryAlgorithm malloc"<<endl; }
    virtual ~IBinaryAlgorithm() { cout<<"IBinaryAlgorithm free"<<endl; }
    virtual int calc(int l, int r) const = 0;
};

#define CALC_METHOD(op) \
    int calc(int l,int r) const override { return l op r; }

/*!
 * Concrete Strategy -Add
 */
class AddAlgo : public IBinaryAlgorithm {
public:
    CALC_METHOD(+)
};

/*!
 * Concrete Strategy -Minus
 */
class MinusAlgo : public IBinaryAlgorithm {
    CALC_METHOD(-)
};

/*!
 * Concrete Strategy -Multipy
 */
class MultipyAlgo : public IBinaryAlgorithm {
    CALC_METHOD(*)
};

/*!
 * Concrete Strategy -Divide
 */
class DivideAlgo : public IBinaryAlgorithm {
    CALC_METHOD(/)
};

typedef shared_ptr<IBinaryAlgorithm> BAlgorithmSP;

/*!
 * Context class
 */
class AlgoContext {
public:
    AlgoContext() {}
    void setAlgorithm(const BAlgorithmSP& algo) { m_algo = algo; }
    BAlgorithmSP getAlgorithm() const { return m_algo; }

    bool hasAlgorithm() const { return bool(m_algo); }
    int calc(int l, int r) const{
        if(!hasAlgorithm()) return -9999;
        return m_algo->calc(l,r);
    }

    void showCalc(int l, int r) const {
        if(!hasAlgorithm()) {
            cout<<"no algorithm selected"<<endl;
            return ;
        }
        cout<<"l?r="<<calc(l,r)<<endl<<endl;
    }
private:
    BAlgorithmSP m_algo;
};

int main() {
    AlgoContext context;
    context.showCalc(10,20);
    context.setAlgorithm(BAlgorithmSP(new AddAlgo));
    context.showCalc(10,20);

    context.setAlgorithm(BAlgorithmSP(new MinusAlgo));
    context.showCalc(10,20);

    context.setAlgorithm(BAlgorithmSP(new MultipyAlgo));
    context.showCalc(10,20);

    context.setAlgorithm(BAlgorithmSP(new DivideAlgo));
    context.showCalc(10,20);

    return 0;
}

