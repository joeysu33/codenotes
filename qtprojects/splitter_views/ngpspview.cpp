#include "ngpspview.h"
#include "ispview.h"
#include "ngpminisplitter.h"

#include <QStackedLayout>
#include <QApplication>

class NGPSPViewPrivate {
public:
    NGPSPViewPrivate(ISPView *view, NGPSPViewOrSplitter *viewOrSplitter, NGPSPView *obj):
        m_obj(obj),
        m_viewOrSplitter(viewOrSplitter) {
        Q_ASSERT(view);
        Q_ASSERT(viewOrSplitter);
        Q_ASSERT(obj);
        m_stack = new QStackedLayout(m_obj);
        m_stack->setMargin(0);
        m_stack->setSpacing(0);
        m_obj->setLayout(m_stack);
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
//            view->widget()->setParent(m_obj);
            m_stack->addWidget(view->widget());
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
    NGPSPView *m_obj  {Q_NULLPTR};
    QStackedLayout *m_stack {Q_NULLPTR};
};

//============NGPSPView==============
NGPSPView::~NGPSPView()
{
    delete m_d;
}

ISPView *NGPSPView::getContentView() const
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
    return m_d->m_viewOrSplitter;
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
    m_d->m_viewOrSplitter = sp;
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
public:
    NGPSPViewOrSplitterPrivate(NGPSPView*view, NGPSPViewOrSplitter *obj) {
        Q_ASSERT(view);
        m_obj = obj;
        m_view = view;
        m_stack = new QStackedLayout(obj);
        m_obj->setLayout(m_stack);
        m_stack->setSpacing(0);
        m_stack->setMargin(0);
        m_stack->setSizeConstraint(QLayout::SetNoConstraint);
        m_view->setParent(m_obj);
        m_stack->addWidget(m_view);
    }

    ~NGPSPViewOrSplitterPrivate() {
        if(m_splitter) {
            delete m_splitter;
        }
        if(m_view) {
            delete m_view;
        }
        delete m_stack;
    }

    NGPSPView* splitByView(ISPView* view, NGPSPViewOrSplitter::SplitOrientation orien) {
        if(!view) return Q_NULLPTR;
        Q_ASSERT(m_view);
        Q_ASSERT(!m_splitter);

        NGPSPView *ret = new NGPSPView(m_obj, view, m_splitter);
        if(!ret) {
            Q_ASSERT_X(false, "NGPSPViewOrSplitter", "malloc memory error!");
            return Q_NULLPTR;
        }

        emit m_obj->aboutToAdd(view->widget());
        m_stack->removeWidget(m_view);
        m_splitter = new NGPMiniSplitter(m_obj);
        QList<NGPSPView*> widgets;
        switch(orien) {
        case NGPSPViewOrSplitter::SO_LEFT: {
            m_splitter->setOrientation(Qt::Horizontal);
            widgets << ret << m_view;
            break;
        }
        case NGPSPViewOrSplitter::SO_RIGHT: {
            m_splitter->setOrientation(Qt::Horizontal);
            widgets << m_view << ret;
            break;
        }
        case NGPSPViewOrSplitter::SO_TOP: {
            m_splitter->setOrientation(Qt::Vertical);
            widgets << ret << m_view;
            break;
        }
        case NGPSPViewOrSplitter::SO_BOTTOM: {
            m_splitter->setOrientation(Qt::Vertical);
            widgets << m_view << ret;
            break;
        }
        }
        for(NGPSPView*w : widgets) {
            m_splitter->addWidget(new NGPSPViewOrSplitter(w, m_obj));
        }
        m_view = Q_NULLPTR;
        m_stack->addWidget(m_splitter);
        m_stack->setCurrentWidget(m_splitter);
        emit m_obj->finishToAdd(ret);
        return ret;
    }

    NGPSPView* splitByWidget(QWidget *w, NGPSPViewOrSplitter::SplitOrientation orien) {
        if(!w) return Q_NULLPTR;
        return splitByView(new ISPView(w), orien);
    }

    NGPSPView* splitByDuplicate(NGPSPViewOrSplitter::SplitOrientation orien) {
        ISPView *iv = m_view->getContentView();
        Q_ASSERT(iv);
        if(!iv->duplicateSupported()) return Q_NULLPTR;
        return splitByView(iv->duplicate(), orien);
    }

    bool unsplitByWidget(QWidget *content) {
        return unsplitBySPView(findViewForQWidget(content));
    }

    bool unsplitByView(ISPView *iv) {
        return unsplitBySPView(findViewForSPView(iv));
    }

    int viewIndexInSplitter(NGPSPView *view) {
        if(!isSplitter()) return -1;
        for(int i=0; i<m_splitter->count(); ++i) {
            if(NGPSPViewOrSplitter * s =
                    qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(i))) {
                if(s->getView() == view) return i;
            }
        }
        return -1;
    }

    bool unsplitBySPView(NGPSPView *view) {
        Q_ASSERT(m_splitter && m_splitter->count() == 2);
        if(!isSplitter()) {
            m_err = NGPSPViewOrSplitter::tr("It's not splitter, can't split!");
            return false;
        }
        if(!view) {
            m_err = NGPSPViewOrSplitter::tr("Invalid view pointer!");
            return false;
        }
        int index = viewIndexInSplitter(view);
        if(index < 0) {
            m_err = NGPSPViewOrSplitter::tr("This view is not belong to splitter.");
            return false;
        }

        QWidget* moveWidget {view->getContentAsWidget()};

        NGPSPViewOrSplitter* m =
            qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(index));
        NGPSPViewOrSplitter* s =
            qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(index?0:1));
        Q_ASSERT(s);
        Q_ASSERT(m);
        if(m->isSplitter() || s->isSplitter()) {
            m_err = NGPSPViewOrSplitter::tr("There's some splitter is not unsplit.");
            return false;
        }
//        if(s->isSplitter()) {
//            //recusively process, always remove first one
//            if(!s->removeByDuplicate()) {
//                return false;
//            }
//        }

        emit m_obj->aboutToRemove(view);
        m_splitter->hide();
        m_stack->removeWidget(m_splitter);
        //record some focus
        bool hadFocus = false;
        if (QWidget *w = view->getContentAsWidget()) {
            if (w && w->hasFocus()) {
                w->clearFocus();
                hadFocus = true;
            }
        }

        s->hide();
        s->setParent(Q_NULLPTR);
        //TODO: consider s is a splitter
        NGPSPView* v= s->getView();
        s->m_d->m_view = Q_NULLPTR;
        delete m_splitter;
        m_splitter = Q_NULLPTR;
        if(v)
            v->setParentSplitterOrView(m_obj);
        m_view = v;
        m_stack->addWidget(m_view);
        m_stack->setCurrentWidget(m_view);
        m_view->show();

         // restore some focus
        if (hadFocus) {
            if (QWidget* w= m_view->getContentAsWidget())
                w->setFocus();
            else
                m_view->setFocus();
        }

        emit m_obj->finishToRemove(moveWidget);
        return true;
    }

    bool unsplitByDuplicate() {
        return unsplitBySPView(qobject_cast<NGPSPView*>(m_splitter->widget(0)));
    }

    bool isSplitter() const { return m_splitter ;}
    bool isView() const { return m_view; }

    NGPSPView* findViewForSPView(ISPView *view) const {
        if(!view) return Q_NULLPTR;
        if(isSplitter()) {
            for(int i=0; i<m_splitter->count(); ++i) {
                if(NGPSPViewOrSplitter * s =
                        qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(i))) {
                    if(NGPSPView* v= s->getView()) {
                        if(v->getContentView() == view) {
                            return v;
                        }
                    }
                }
            }
        } else {
            if(m_view->getContentView() == view) {
                return m_view;
            }
        }

        return Q_NULLPTR;
    }

    NGPSPView* findViewForQWidget(QWidget* content) const {
        if(!content) return Q_NULLPTR;
        if(isSplitter()) {
            for(int i=0; i<m_splitter->count(); ++i) {
                if(NGPSPViewOrSplitter * s =
                        qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(i))) {
                    if(NGPSPView* view = s->getView()) {
                        if(view->getContentAsWidget() == content) {
                            return view;
                        }
                    }
                }
            }
        } else {
            if(content == m_view->getContentAsWidget()) {
                return m_view;
            }
        }

        return Q_NULLPTR;
    }

    NGPSPView* findViewForSPViewRecursively(ISPView *view) const {
        if(!view) return Q_NULLPTR;
        if(isSplitter()) {
            for(int i=0; i<m_splitter->count(); ++i) {
                if(NGPSPViewOrSplitter* s =
                        qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(i))) {
                    if(NGPSPView* r = s->m_d->findViewForSPViewRecursively(view)) {
                        return r;
                    }
                }
            }
        } else {
            return findViewForSPView(view);
        }

        return Q_NULLPTR;
    }

    NGPSPView* findViewForQWidgetRecursively(QWidget* content) const {
        if(isView()) {
            return findViewForQWidget(content);
        }

        for(int i=0; i<m_splitter->count(); ++i) {
            if(NGPSPViewOrSplitter* s =
                    qobject_cast<NGPSPViewOrSplitter*>(m_splitter->widget(i))) {
                if(NGPSPView *r = s->m_d->findViewForQWidget(content)) {
                    return r;
                }
            }
        }

        return Q_NULLPTR;
    }

public:
    QString m_err;
    QStackedLayout *m_stack {Q_NULLPTR};
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

NGPSPViewOrSplitter::~NGPSPViewOrSplitter()
{
    delete m_d;
}

NGPSPView *NGPSPViewOrSplitter::add(QWidget *content, NGPSPViewOrSplitter::SplitOrientation orentation)
{
    return m_d->splitByWidget(content, orentation);
}

NGPSPView *NGPSPViewOrSplitter::add(ISPView *view, NGPSPViewOrSplitter::SplitOrientation orientation)
{
    return m_d->splitByView(view, orientation);
}

NGPSPView *NGPSPViewOrSplitter::addByDuplicate(NGPSPViewOrSplitter::SplitOrientation orientation)
{
    return m_d->splitByDuplicate(orientation);
}

bool NGPSPViewOrSplitter::remove(QWidget *content)
{
    return m_d->unsplitByWidget(content);
}

bool NGPSPViewOrSplitter::remove(ISPView *view)
{
    return m_d->unsplitByView(view);
}

bool NGPSPViewOrSplitter::remove(NGPSPView *sview)
{
    return m_d->unsplitBySPView(sview);
}

bool NGPSPViewOrSplitter::removeByDuplicate()
{
    return m_d->unsplitByDuplicate();
}

NGPSPViewOrSplitter *NGPSPViewOrSplitter::findParentViewOrSplitter() const
{
    QWidget *p {parentWidget() };
    while(p) {
        if(NGPSPViewOrSplitter *s = qobject_cast<NGPSPViewOrSplitter*>(p)) {
            return s;
        }
        p = p->parentWidget();
    }

    return Q_NULLPTR;
}

bool NGPSPViewOrSplitter::isSplitter() const
{
    return m_d->isSplitter();
}

bool NGPSPViewOrSplitter::isView() const
{
    return m_d->isView();
}

NGPSPView *NGPSPViewOrSplitter::getView() const
{
    return (isView()) ?m_d->m_view : Q_NULLPTR;
}

QSplitter *NGPSPViewOrSplitter::getSplitter() const
{
    return (isSplitter()) ? m_d->m_splitter : Q_NULLPTR;
}

NGPSPView *NGPSPViewOrSplitter::findViewForSPView(ISPView *view) const
{
    return m_d->findViewForSPView(view);
}

NGPSPView *NGPSPViewOrSplitter::findViewForQWidget(QWidget *content) const
{
    return m_d->findViewForQWidget(content);
}

NGPSPView *NGPSPViewOrSplitter::findViewForSPViewRecursively(ISPView *view) const
{
    return m_d->findViewForSPViewRecursively(view);
}

NGPSPView *NGPSPViewOrSplitter::findViewForQWidgetRecursively(QWidget *content) const
{
    return m_d->findViewForQWidgetRecursively(content);
}

Qt::Orientation NGPSPViewOrSplitter::getSplitOrientation() const
{
    if(!isSplitter()) return Qt::Horizontal;
    return m_d->m_splitter->orientation();
}

void NGPSPViewOrSplitter::setSplitOrientation(Qt::Orientation orien)
{
    if(isSplitter() && m_d->m_splitter->orientation() == orien) {
        m_d->m_splitter->setOrientation(orien);
    }
}

ISPView *NGPSPViewOrSplitter::getContentAsView() const
{
    if(!isView()) return Q_NULLPTR;
    return m_d->m_view->getContentView();
}

QString NGPSPViewOrSplitter::getError() const
{
    return m_d->m_err;
}

void NGPSPViewOrSplitter::init(ISPView *iv)
{
    m_d = new NGPSPViewOrSplitterPrivate(new NGPSPView(this,iv, this), this);
}

NGPSPViewOrSplitter::NGPSPViewOrSplitter(NGPSPView *view, QWidget *parent)
    :QWidget(parent)
{
    m_d = new NGPSPViewOrSplitterPrivate(view, this);
}

