#ifndef SRC1_1_H
#define SRC1_1_H

/*!
   \defgroup groupa 数据平台
这个分组是用来对数据平台进行测试的.....
*/

/*!
  \ingroup groupa
 * \brief The Src11 class
 * 这是一个测试基类
 */
class Src11 {
public:
    /*!
     * \brief Src11
     * 这是一个Src11的构造函数
     */
    Src11() {}
public:
    /*!
     * \brief add 加法
     * \param a 参数a
     * \param b 参数b
     */
    void add(int a, int b) ;

    /*!
     * \brief sub 减法
     * \param a 参数a
     * \param b 参数b
     */
    void sub(int a, int b);

    /*!
     * \brief func 测试函数
     * \param a 参数a
     * \param b 参数b
     * \param c 参数c
     */
    virtual void func(int a, const char* b, double c) ;

    /*!
     * \brief func2 虚函数func2
     * \param a 参数a
     * \param b 参数b
     */
    virtual void func2(int a, char b);

    /*!
     * \brief func3 纯虚函数func3
     * \return  返回一个整型
     */
    virtual int func3() const = 0;
}

#endif // SRC1_1_H
