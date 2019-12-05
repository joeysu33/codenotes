#ifndef SRC2_3_H
#define SRC2_3_H

#include "src2_1.h"
#include "src2_2.h"

/*!
  \ingroup groupc
 * \brief The Src23 class
 * 这份奇偶奇偶风刀霜剑偶就发动机萨芬
 */
class Src23 : public Src21, public Src22 {
public:
    /*!
     * \brief Src23 构造函数测骄傲j试
     * \param a fjofjowjef
     * \param b jfodjsofjojweojfowjfo
     */
    Src23(int a, int b) : m_a(a), m_b(b) {}

    /*!
     * \brief test1 fjoejwofjowfjo
     */
    void test1();

    /*!
     * \brief test2 讲佛经额哦发文件哦放假
     * \param x fojjfowjeofjwo
     * \param y jfoejowfjowjf
     */
    void test2(double x, double y);
private:
    /*! 成员变量m_a, m_b */
    int m_a{0}, m_b {-1};
};

#endif // SRC2_3_H
