#if !defined(_NGPMINISPLITTER_INCLUDED_H)
#define _NGPMINISPLITTER_INCLUDED_H

#include <QSplitter>

class QSplitterHandle;

class NGPMiniSplitter : public QSplitter
{
public:
    enum SplitterStyle {Dark, Light};

    NGPMiniSplitter(QWidget *parent = 0, SplitterStyle style = Dark);
    NGPMiniSplitter(Qt::Orientation orientation, SplitterStyle style = Dark);

protected:
    QSplitterHandle *createHandle() Q_DECL_OVERRIDE;

private:
    SplitterStyle m_style;
};

#endif //_NGPMINISPLITTER_INCLUDED_H
