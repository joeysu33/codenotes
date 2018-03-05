#include "ultraviewmanager.h"
#include "iview.h"
#include "editorview.h"
#include "utils.h"
#include "qtcassert.h"

#include <QApplication>

namespace {
    static UltraViewManager * g_instance{ Q_NULLPTR};
}
UltraViewManager *UltraViewManager::instance()
{
    if(g_instance) return g_instance;
    g_instance = new UltraViewManager();
    return g_instance;
}

//void UltraViewManager::closeView(IView *view)
//{
//    if(!view) return ;
////    emptyEditorView(view);

//    SplitterOrView *splitterOrView = view->parentSplitterOrView();
//    Q_ASSERT(splitterOrView);
//    Q_ASSERT(splitterOrView->view() == view);
//    SplitterOrView *splitter = splitterOrView->findParentSplitter();
//    Q_ASSERT(splitterOrView->hasEditors() == false);
//    splitterOrView->hide();
//    delete splitterOrView;

//    splitter->unsplit();

//    EditorView *newCurrent = splitter->findFirstView();
//    if (newCurrent) {
////        EditorManagerPrivate::activateView(newCurrent);
//        UltraViewManager::instance()->activateEditorView(newCurrent);
//    }
//}

IView *UltraViewManager::currentView()
{
    return g_instance->m_currentView;
}

void UltraViewManager::setCurrentView(IView *view)
{
    if(!view) setCurrentEditorView(Q_NULLPTR);
    if(g_instance->m_currentView == view) return ;
    emit UltraViewManager::instance()->currentViewAboutToChanged(g_instance->m_currentView);

    g_instance->m_currentView = view;
    if(view) {
        if(EditorView *ev = viewForEditor(view)) {
            ev->setCurrentEditor(view);
        }
    }
    emit UltraViewManager::instance()->currentViewChanged(view);
}

void UltraViewManager::closeView(IView *v)
{
    Q_UNUSED(v);
}

EditorView *UltraViewManager::currentEditorView()
{
    return UltraViewManager::instance()->getCurrentView();
}

void UltraViewManager::splitNewWindow(EditorView *ev)
{
    Q_UNUSED(ev);
    //TODO
//    IView* view = ev->currentEditor();
//    IView* newView= 0;
//    if (view && view->duplicateSupported())
//        newView = duplicateView(view);
//    else
//        newView = editor; // move to the new view

    //TODO more implementation
//    auto win = new EditorWindow;
//    EditorArea *area = win->editorArea();
//    d->m_editorAreas.append(area);
//    connect(area, &QObject::destroyed, d, &EditorManagerPrivate::editorAreaDestroyed);
//    win->show();
//    Utils::raiseWindow(win);
//    if (newView)
//        activateEditor(area->view(), newView, EditorManager::IgnoreNavigationHistory);
//    else
//        area->view()->setFocus();
}

IView *UltraViewManager::duplicateView(IView *v)
{
    if(!v) return Q_NULLPTR;
    if(!v->duplicateSupported()) return Q_NULLPTR;
    return v->duplicate();
}

void UltraViewManager::emptyEditorView(EditorView *ev)
{
    //TODO
    if(!ev) return ;
//    QList<IView*> views = ev->editors();
//    for(IView *v : views) {
//        if(currentView() == v) {
//            setCurrentEditorView(ev);
//            setCurrentView(0);
//        }
//        views.removeAll(v);
//        ev->removeEditor(v);
    //    }
}

EditorView *UltraViewManager::viewForEditor(IView *v)
{
    QWidget *w = v->widget();
    while(w) {
        w = w->parentWidget();
        if(EditorView *view = qobject_cast<EditorView*>(w)) {
            return view;
        }
    }

    return Q_NULLPTR;
}

void UltraViewManager::setCurrentEditorView(EditorView *ev)
{
    if(ev == g_instance->m_current) return ;
    EditorView *old {g_instance->m_current };
    g_instance->m_current = ev;

    if(old) old->update();
    if(ev) ev->update();
}

EditorView *UltraViewManager::getCurrentView()
{
    return g_instance->m_current;
}

void UltraViewManager::closeEditorView(EditorView *ev)
{
    if (!ev)
        return;

    //Must don't have any sub editors
    emptyEditorView(ev);

    SplitterOrView *splitterOrView = ev->parentSplitterOrView();
    Q_ASSERT(splitterOrView);
    Q_ASSERT(splitterOrView->view() == ev);
    SplitterOrView *splitter = splitterOrView->findParentSplitter();
    Q_ASSERT(splitterOrView->hasEditors() == false);
    splitterOrView->hide();
    delete splitterOrView;

    splitter->unsplit();

    EditorView *newCurrent = splitter->findFirstView();
    if (newCurrent) {
//        EditorManagerPrivate::activateView(newCurrent);
        activateEditorView(ev);
    }
}

void UltraViewManager::activateEditorView(EditorView *ev)
{
    if(!ev) return ;
    QTC_ASSERT(ev, return);
    QWidget *focusWidget;
    if (IView* v= ev->currentEditor()) {
        setCurrentView(v);
        focusWidget = v->widget();
    } else {
        setCurrentEditorView(ev);
        focusWidget = ev;
    }
    focusWidget->setFocus();
    Utils::raiseWindow(focusWidget);
}

void UltraViewManager::onFocusChange(QWidget *old, QWidget *now)
{
    Q_UNUSED(old)
    Q_UNUSED(now)

//    Q_UNUSED(old)
//    // only interesting if the focus moved within the editor area
//    if (!focusWidget() || focusWidget() != now)
//        return;
//    // find the view with focus
//    EditorView *current = findFirstView();
//    while (current) {
//        if (current->focusWidget() && current->focusWidget() == now) {
//            setCurrentView(current);
//            break;
//        }
//        current = current->findNextView();
//    }
}

UltraViewManager::UltraViewManager()
{
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), SLOT(onFocusChange(QWidget*,QWidget*)));
}
