#if !defined(_IVIEW_INCLUDED_H)
#define _IVIEW_INCLUDED_H

//#include <coreplugin/core_global.h>
//#include <coreplugin/icontext.h>

#include <QMetaType>
#include <QPointer>
#include <QWidget>

class IView : public QObject
{
    Q_OBJECT

public:
    IView(QObject *parent = 0);

    bool duplicateSupported() const;
    void setDuplicateSupported(bool duplicateSupported);

//    virtual IDocument *document() = 0;

    virtual IView *duplicate() { return Q_NULLPTR; }
    virtual QWidget* widget() const  { return m_widget; }
    virtual void setWidget(QWidget * widget) { m_widget = widget; }

    virtual QByteArray saveState() const { return QByteArray(); }
    virtual bool restoreState(const QByteArray &/*state*/) { return true; }

//    virtual int currentLine() const { return 0; }
//    virtual int currentColumn() const { return 0; }
//    virtual void gotoLine(int line, int column = 0, bool centerLine = true) { Q_UNUSED(line) Q_UNUSED(column) Q_UNUSED(centerLine) }

    virtual QWidget *toolBar() = 0;

//    virtual bool isDesignModePreferred() const { return false; }

private:
    bool m_duplicateSupported;
    QPointer<QWidget> m_widget;
};


Q_DECLARE_METATYPE(IView*)

#endif //_IVIEW_INCLUDED_H
