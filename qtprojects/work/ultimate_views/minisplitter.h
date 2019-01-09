#if !defined(_MINISPLITTER_INCLUDED_H)
#define _MINISPLITTER_INCLUDED_H

#include <QSplitter>

class QSplitterHandle;

class MiniSplitter : public QSplitter
{
public:
    enum SplitterStyle {Dark, Light};

    MiniSplitter(QWidget *parent = 0, SplitterStyle style = Dark);
    MiniSplitter(Qt::Orientation orientation, SplitterStyle style = Dark);

protected:
    QSplitterHandle *createHandle() Q_DECL_OVERRIDE;

private:
    SplitterStyle m_style;
};

#endif //_MINISPLITTER_INCLUDED_H
