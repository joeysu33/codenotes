#ifndef ISPVIEW_H
#define ISPVIEW_H

#include <QPointer>
#include <QWidget>
/*!
 * \brief The ISPView class
 * 抽象View，仅用来维护QWidget，并不会管理QWidget的内存释放
 */
class ISPView
{
public:
    ISPView(QWidget* w = Q_NULLPTR) :m_widget(w) {}
    virtual ~ISPView() {}
    virtual bool duplicateSupported() const { return m_duplicateSupported; }
    virtual void setDuplicateSupported(bool duplicateSupported) { m_duplicateSupported =duplicateSupported;}

    virtual ISPView* duplicate() { return Q_NULLPTR; }
    virtual QWidget* widget() const  { return m_widget; }
    virtual void setWidget(QWidget * widget) { m_widget = widget; }
private:
    bool m_duplicateSupported {false};
    QPointer<QWidget> m_widget;
};

#endif // ISPVIEW_H
