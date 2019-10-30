#include "testlib2.h"


/*!
  \class TestLib2
  \brief This class is for just testing
  AABVJJLFJLDJFLJF
  AABVJJLFJLDJFLJF
  AABVJJLFJLDJFLJF
  AABVJJLFJLDJFLJF
  Access \l {https://www.douban.com}
  \inmodule Test
*/
TestLib2::TestLib2() {
}


/*!
 \a a the parameter of a
 \a b the parameter of b
 \brief TestLib2::add
 Returns result of add:
*/
int TestLib2::add(int a, int b) { 
    return a+b;
}

/*!
  \brief TestLib2::sub
  \a a sub/a
  \a b sub/b
*/
int TestLib2::sub(int a, int b) {
    return a-b;
}


/*!
  \brief TestLib2::mul
  \a a mul/a
  \a b mul/b
 */
int TestLib2::mul(int a, int b) {
    return a*b;
}


/*!
  \brief TestLib2::addPriv
  \a a addPriv/a
  \a b addPriv/b
 */
int TestLib2::addPriv(int a, int b) {
    return add(a,b);
}

/*!
  \brief TestLib2::addProt
  \a a addProt/a
  \a b addProt/b
 */
int TestLib2::addProt(int a, int b) {
    return add(a,b);
}



