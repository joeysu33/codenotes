/*!
 * 设计模式 备忘录(Memento)
 * 别名:Token
 * 作用:
 * 记录一个对象某一时刻的特定状态
 * 等到一定时候对该状态进行恢复
 * 角色:
 * Originator 原发器:调用备忘录的所有信息，允许原发器访问返回到先前状态
 * Memento 备忘录:
 * Caretaker 负责人:只负责备忘录的保存并将备忘录传递给其他对象。
 * 其他对象: 只需要从负责人处取出备忘录对象，并将原发器的状态进行恢复，无须关心备忘录的保存恢复细节
 * -------------------------------------------------------------------------------------------------
 * 案例: (某公司多年的财务报表)
 * Caretaker,负责保管财务报表的人，不允许对备忘录的信息进行修改和检查
 * Memento,可以是电子记录（磁盘/光盘），也可以是纸质记录,由公司会计负责写入
 * Originator,公司的财务信息(某年/某月)
 * 注意事项:
 * Memento的封装性，其他对象不能创建和访问Memento,只有Originator可以
 */

#include <string>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <memory>

using namespace std;
/*!
 * 一条流水记录
 */
struct Record {
    Record(const Record& r) {
        m_value = r.m_value;
        m_reason = r.m_reason;
        m_from = r.m_from;
        m_to = r.m_to;
    }

    Record(float v, const string& from, const string& to, const string& reason) {
        m_value = v;
        m_from = from;
        m_to = to;
        m_reason= reason;
    }
    Record() {m_value = 0; }
    ~Record() {}

    /*!资金的数额*/
    float m_value {0};
    /*!资金发生的记录*/
    string m_reason;
    /*!资金的来源*/
    string m_from;
    /*!资金的去向*/
    string m_to;
};

typedef std::shared_ptr<Record> RecordSP;

/*!
 * 公司资金流水状态(流水的实际数据)
 * 本类会集成在cpp中，不对外开放
 */
struct CompanyCapticalFlowState {
    CompanyCapticalFlowState() {}
    CompanyCapticalFlowState(const string& company):m_companyName(company) {}
    CompanyCapticalFlowState* clone() const{
        CompanyCapticalFlowState *newS = new CompanyCapticalFlowState(m_companyName);
        for(const RecordSP& r : m_records) {
            newS->m_records.push_back(RecordSP(new Record(*r.get())));
        }
        return newS;
    }

    void transfter(const string& to, float v, const string& reason= string()) {
        RecordSP r (new Record(v, m_companyName, to, reason));
        m_records.push_back(r);
    }

    void income(const string& from, float v, const string& reason = string()) {
        RecordSP r(new Record(v, from ,m_companyName, reason));
        m_records.push_back(r);
    }

    float bookAmount() const {
        float flow=0;
        for(const RecordSP &sp : m_records) {
            if(sp->m_from == m_companyName) {
                flow -= sp->m_value;
            } else {
                flow += sp->m_value;
            }
        }

        return flow;
    }

    void showState() const {
        for(const RecordSP& r : m_records) {
            printf("!!!!from: %s, to:%s, amount:%.3f,reason:%s.\n",
                    r->m_from.c_str(), r->m_to.c_str(), r->m_value, r->m_reason.c_str());
        }
        printf("account left:%.3f.\n", bookAmount());
        printf("---------------------------------\n");
    }
private:
    vector<RecordSP> m_records;
    string m_companyName;
};
typedef shared_ptr<CompanyCapticalFlowState> CompanyCapticalFlowStateSP;

/*!
 * Memento 备忘录，对某时刻流水进行备忘
 */
class CapticalFlowMemento {
public:
    ~CapticalFlowMemento() {}
    bool valid() const { return !!m_state;}
private:
    /*!保存数据封装性、只能由Originator构建*/
    CapticalFlowMemento(CompanyCapticalFlowState* s) {
        assert(s);
        if(s)
            m_state = CompanyCapticalFlowStateSP(s->clone());
    }
    friend class CompanyCaptialFlow;
private:
    CompanyCapticalFlowStateSP m_state;
};

typedef shared_ptr<CapticalFlowMemento> CapticalFlowMementoSP;

/*!
 * 公司账面流水,角色Originator
 */
class CompanyCaptialFlow {
public:
    CompanyCaptialFlow() {
        m_state.reset(new CompanyCapticalFlowState(getName()));
    }

    CapticalFlowMementoSP createMemento() {
        return CapticalFlowMementoSP(new CapticalFlowMemento(m_state.get()));
    }

    void setCapticalFlowMemento(const CapticalFlowMementoSP& sp) {
        m_state = sp->m_state;
    }

    void transferToSalary(const string& name, float salary) {
        m_state->transfter(name, salary, "salary");
    }

    void dailyExpenses(float expense){
        m_state->transfter("<dailyExpenses>", expense, "dailyExpenses");
    }

    void incomeGame(float v) {
        m_state->income("game", v, "game");
    }

    void incomeVedio(float v) {
        m_state->income("vedio", v, "vedio");
    }

    void show() const {
        m_state->showState();
    }
protected:
    string getName() const { return "ds.company"; }
private:
    CompanyCapticalFlowStateSP m_state;
};

/*!
 * 负责档案管理的人
 */
class Caretaker {
public:
    void addMemento(const CapticalFlowMementoSP& memento) {
        if(!memento) return ;
        m_mementos.push_back(memento);
    }

    /*!
     * 可以构建按照日期来读取备忘记录
     */
    CapticalFlowMementoSP getMementoByIndex(int index) {
        if(index <0 || index >= m_mementos.size()) return CapticalFlowMementoSP();
        return m_mementos[index];
    }

    CapticalFlowMementoSP takeMementoByIndex(int index) {
        if(index < 0 || index>=m_mementos.size()) return CapticalFlowMementoSP();
        CapticalFlowMementoSP r = m_mementos[index];
        m_mementos.erase(m_mementos.begin() + index);
        return r;
    }

    unsigned size() const { return m_mementos.size(); }
private:
    vector<CapticalFlowMementoSP> m_mementos;
};

int main() {
    Caretaker taker;
    CompanyCaptialFlow flow;

    flow.transferToSalary("zhangsan", 10000.322312);
    flow.transferToSalary("lisi", 10000.4323);
    taker.addMemento(flow.createMemento());
    flow.show();

    flow.incomeGame(30000.323);
    flow.show();

    flow.incomeGame(10000.4343);
    flow.incomeGame(30000.90943);
    flow.show();
    taker.addMemento(flow.createMemento());

    /*!精确的恢复原对象状态*/
    flow.setCapticalFlowMemento(taker.takeMementoByIndex(0));
    flow.show();

    return 0;
}

