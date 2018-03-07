#include "ngpminisplitter.h"

#include <QPaintEvent>
#include <QPainter>
#include <QSplitterHandle>

class NGPMiniSplitterHandle : public QSplitterHandle
{
public:
    NGPMiniSplitterHandle(Qt::Orientation orientation, QSplitter *parent, bool lightColored = false)
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


void NGPMiniSplitterHandle::resizeEvent(QResizeEvent *event)
{
    if (orientation() == Qt::Horizontal)
        setContentsMargins(2, 0, 2, 0);
    else
        setContentsMargins(0, 2, 0, 2);
    setMask(QRegion(contentsRect()));
    QSplitterHandle::resizeEvent(event);
}

void NGPMiniSplitterHandle::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QColor color(128,128, 0);
    if(NGPMiniSplitter* splitter = qobject_cast<NGPMiniSplitter*>(parentWidget())) {
        color = splitter->m_handleColor;
    }
    painter.fillRect(rect(), color);
}

QSplitterHandle *NGPMiniSplitter::createHandle()
{
    return new NGPMiniSplitterHandle(orientation(), this, m_style == Light);
}

NGPMiniSplitter::NGPMiniSplitter(QWidget *parent, SplitterStyle style)
    : QSplitter(parent),
      m_style(style)
{
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setHandleColorByStyle(style);
}

NGPMiniSplitter::NGPMiniSplitter(Qt::Orientation orientation, SplitterStyle style)
    : QSplitter(orientation),
      m_style(style)
{
    setHandleWidth(1);
    setChildrenCollapsible(false);
    setHandleColorByStyle(style);
}

void NGPMiniSplitter::setHandleColor(const QColor &color)
{
    m_handleColor = color;
}

void NGPMiniSplitter::setHandleColorByStyle(NGPMiniSplitter::SplitterStyle style)
{
    if(style == Dark) {
        m_handleColor = QColor(128, 128, 128);
    } else {
        m_handleColor = QColor(128,128, 0);
    }
}

QColor NGPMiniSplitter::getHandleColor() const
{
    return m_handleColor;
}
