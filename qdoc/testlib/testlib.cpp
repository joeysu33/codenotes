#include "testlib.h"


/*!
  \class TestLib
  \brief This class is for just testing
  AABVJJLFJLDJFLJF
  AABVJJLFJLDJFLJF
  AABVJJLFJLDJFLJF
  AABVJJLFJLDJFLJF
  Access \l {https://www.douban.com}
*/
TestLib::TestLib() {
}


/*!
 \a a the parameter of a
 \a b the parameter of b
 \brief TestLib::add
 Returns result of add:
*/
int TestLib::add(int a, int b) { 
    return a+b;
}

/*!
  \brief TestLib::sub
  \a a sub/a
  \a b sub/b
*/
int TestLib::sub(int a, int b) {
    return a-b;
}


/*!
  \brief TestLib::mul
  \a a mul/a
  \a b mul/b
 */
int TestLib::mul(int a, int b) {
    return a*b;
}


/*!
  \brief TestLib::addPriv
  \a a addPriv/a
  \a b addPriv/b
 */
int TestLib::addPriv(int a, int b) {
    return add(a,b);
}

/*!
  \brief TestLib::addProt
  \a a addProt/a
  \a b addProt/b
 */
int TestLib::addProt(int a, int b) {
    return add(a,b);
}



