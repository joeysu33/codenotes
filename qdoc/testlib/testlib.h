#if !defined(TESTLIB_INCLUDEDE_H_)
#define TESTLIB_INCLUDEDE_H_

class TestLib {
public:
    TestLib() ;
public:
    int add(int a, int b);
    int sub(int a, int b);
    int mul(int a, int b);
protected:
    int addProt(int a, int b);
private:
    int addPriv(int a,int b);
};

#endif //TESTLIB_INCLUDEDE_H_
