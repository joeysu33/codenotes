#include "minisplitter.h"

//#include <utils/stylehelper.h>
//#include <utils/theme/theme.h>

#include <QPaintEvent>
#include <QPainter>
#include <QSplitterHandle>

class MiniSplitterHandle : public QSplitterHandle
{
public:
    MiniSplitterHandle(Qt::Orientation orientation, QSplitter *parent, bool lightColored = false)
            : QSplitterHandle(orientation, parent),
              m_lightColored(lightColored)
    {
        setMask(QRegion(contentsRect()));
        setAttribute(Qt::WA_MouseNoMask, true);
    }
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool m_lightColored;
};


void MiniSplitterHandle::resizeEvent(QResizeEvent *event)
{
    if (orientation() == Qt::Horizontal)
        setContentsMargins(2, 0, 2, 0);
    else
        setContentsMargins(0, 2, 0, 2);
    setMask(QRegion(contentsRect()));
    QSplitterHandle::resizeEvent(event);
}

void MiniSplitterHandle::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    const QColor color = Utils::creatorTheme()->color(
//                m_lightColored ? Utils::Theme::FancyToolBarSeparatorColor
//                               : Utils::Theme::SplitterColor);
    const QColor color(128, 128, 128);
    painter.fillRect(event->rect(), color);
}

QSplitterHandle *MiniSplitter::createHandle()
{
    return new MiniSplitterHandle(orientation(), this, m_style == Light);
}

MiniSplitter::MiniSplitter(QWidget *parent, SplitterStyle style)
    : QSplitter(parent),
      m_style(style)
{
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setProperty("minisplitter", true);
}

MiniSplitter::MiniSplitter(Qt::Orientation orientation, SplitterStyle style)
    : QSplitter(orientation),
      m_style(style)
{
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setProperty("minisplitter", true);
}
