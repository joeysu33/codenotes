#ifndef SRC1_3_H
#define SRC1_3_H

#include "src1_2.h"

/*!
   \ingroup groupa
 * \brief The Src13 class
 * 这是一个派生自Src12的类
 */
class Src13 : public Src12 {
public:
    /*!
     * \brief Src13
     * 默认构造函数
     */
    Src13() {}

    /*!
     * \brief Src13 非默认构造函数
     * \param x 带参数的构造函数
     */
    Src13(int x): m_x(x) {}

    /*!
     * \brief func5 测试函数func5
     * \param x 参数x
     * \param y 参数y
     */
    void func5(int x, int y);
private:
    /*! 成员变量m_x */
    int m_x;
};

#endif // SRC1_3_H
