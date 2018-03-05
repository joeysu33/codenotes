#include "ngpspview.h"
#include "ispview.h"
#include "ngpminisplitter.h"

#include <QStackedLayout>
class NGPSPViewPrivate {
public:
    NGPSPViewPrivate(ISPView *view, NGPSPViewOrSplitter *viewOrSplitter, NGPSPView *obj):
        m_view(view) ,
        m_obj(obj),
        m_viewOrSplitter(viewOrSplitter) {
        Q_ASSERT(view);
        Q_ASSERT(viewOrSplitter);
        Q_ASSERT(obj);
        m_stack = new QStackedLayout(m_obj);
        m_stack->setMargin(0);
        m_stack->setSpacing(0);
        placeSPView(view);
    }
    ~NGPSPViewPrivate() {
        emptySPView();
    }

    void placeSPView(QWidget *content) {
        placeSPView(new ISPView(content));
    }

    void placeSPView(ISPView *view) {
        if(!view) return ;
        emptySPView();
        if(QWidget *current = m_stack->currentWidget()) {
            m_stack->removeWidget(current);
        }
        if(view->widget()) {
            m_stack->setCurrentWidget(view->widget());
        }
        m_obj->update();
    }

    void emptySPView() {
        if(m_view) {
            delete m_view;
            m_view = Q_NULLPTR;
        }
    }
public:
    NGPSPViewOrSplitter* m_viewOrSplitter{Q_NULLPTR};
    ISPView *m_view {Q_NULLPTR};
    NGPSPView *m_obj {Q_NULLPTR};
    QStackedLayout *m_stack {Q_NULLPTR};
};

//============NGPSPView==============
ISPView *NGPSPView::getContent() const
{
    return m_d->m_view;
}

QWidget *NGPSPView::getContentAsWidget() const
{
    if(!m_d->m_view) return Q_NULLPTR;
    return m_d->m_view->widget();
}

NGPSPViewOrSplitter *NGPSPView::getParentSplitterOrView() const
{
    return m_d->viewOrSplitter;
}

void NGPSPView::setContent(QWidget *content)
{
    m_d->placeSPView(content);
}

void NGPSPView::setContent(ISPView *content)
{
    m_d->placeSPView(content);
}

void NGPSPView::setParentSplitterOrView(NGPSPViewOrSplitter *sp)
{
    Q_ASSERT(sp);
    m_d->viewOrSplitter = sp;
}

NGPSPView::NGPSPView(NGPSPViewOrSplitter *sp, ISPView *content, QWidget *parent)
    :QWidget(parent)
{
    init(sp, content);
}

NGPSPView::NGPSPView(NGPSPViewOrSplitter *sp, QWidget *content, QWidget *parent)
    :QWidget(parent)
{
    init(sp, new ISPView(content));
}

void NGPSPView::init(NGPSPViewOrSplitter *sp, ISPView *content)
{
    m_d = new NGPSPViewPrivate(content, sp, this);
}

//==========NGPSPViewOrSplitterPrivate======

class NGPSPViewOrSplitterPrivate {
    NGPSPViewOrSplitterPrivate(ISPView *iv, NGPSPViewOrSplitter *obj) {
        m_obj = obj;
        m_view = new NGPSPView(m_obj, iv, m_obj);
    }

public:
    NGPSPViewOrSplitter *m_obj{Q_NULLPTR};
    NGPSPView *m_view {Q_NULLPTR};
    NGPMiniSplitter *m_splitter {Q_NULLPTR};
};

NGPSPViewOrSplitter::NGPSPViewOrSplitter(ISPView *view, QWidget *parent)
    :QWidget(parent)
{
    init(view);
}

NGPSPViewOrSplitter::NGPSPViewOrSplitter(QWidget *content, QWidget *parent)
    :QWidget(parent)
{
    init(new ISPView(content));
}

void NGPSPViewOrSplitter::init(ISPView *iv)
{
    m_d = new NGPSPViewOrSplitterPrivate(iv);
}

