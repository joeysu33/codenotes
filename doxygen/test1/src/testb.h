#if !defined(_TESTB_INCLUCED_H_)
#define _TESTB_INCLUCED_H_


/*!
 * \brief 本类B用来处理XXXX */
class B {
public:
    /*!
     * \brief 构造函数
     * \param int a 参数a
     * \param int b 参数b
     */
    B(int a, int b) : m_a(a), m_b(b) {}

    /*!
     * \brief 设置参数D
     * \param void *d 参数d
     * \return 返回NULL
     */
    void setD(void *d) { m_d = d; }

    /*!
     * \brief 获取参数D
     * \return 参数D
     */
    void* getD() const { return m_d; }

protected:
    /*!
     * \brief 设置参数e
     * \param void* e参数e
     * \return 返回NULL
     */
    void setE(void* e) { m_e = e; }

    /*!
     * \brief 获取参数e
     * \return 返回参数e
     */
    void* getE() const { return m_e; }
private:
    int m_a, m_b, m_c;
    void *m_d;
    void *m_e;
};

#endif
