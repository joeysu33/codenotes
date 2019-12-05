#ifndef SRC1_2_H
#define SRC1_2_H

#include "src1_1.h"

/*!
   \defgroup groupb 平台框架
这个分组是用来对平台框架进行测试的.....
*/

/*!
  \ingroup groupb
 * \brief The Src12 class
 * 这是测试类XXX
 */
class Src12 : public Src11 {
public:
    /*!
     * \brief Src12
     * 这是一个默认的构造函数
     */
    Src12() {}
public:
    /*!
     * \brief func3 实现虚函数func3的重写
     * \return  返回一个整数值
     */
    int func3() const override ;

    /*!
     * \brief func4 自定义一个func4函数
     * \param a 参数a
     * \param b 参数b
     * \param c 参数c
     * \param d 参数d
     */
    void func4(int a, int b, char c, const char *d);
} ;

#endif // SRC1_2_H
