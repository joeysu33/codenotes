#include <iostream>

using namespace std;
template<class T, class U>
class TestA {
public:
    template<class V>
    void calltempl(const V& x) const {
        cout<<x<<endl;
    }
};


template<class T, class U>
static void usingTemp(const T& t, const U& u) {
    t.template calltempl<U> (u);
}

int
main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    int x = 100;
    typedef TestA<char, unsigned long>  TestA_ty;
    TestA_ty a;
    usingTemp<TestA_ty, int>(a, x);
}

