#if !defined(_NGPMINISPLITTER_INCLUDED_H)
#define _NGPMINISPLITTER_INCLUDED_H

#include <QSplitter>
#include <QColor>

class QSplitterHandle;

class NGPMiniSplitter : public QSplitter
{
    Q_OBJECT
public:
    enum SplitterStyle {Dark, Light};

    NGPMiniSplitter(QWidget *parent = 0, SplitterStyle style = Dark);
    NGPMiniSplitter(Qt::Orientation orientation, SplitterStyle style = Dark);

    void setHandleColor(const QColor & color);
    void setHandleColorByStyle(SplitterStyle style=Dark);
    QColor getHandleColor() const;
protected:
    QSplitterHandle *createHandle() Q_DECL_OVERRIDE;

private:
    friend class NGPMiniSplitterHandle ;
    SplitterStyle m_style;
    QColor m_handleColor;
};

#endif //_NGPMINISPLITTER_INCLUDED_H
