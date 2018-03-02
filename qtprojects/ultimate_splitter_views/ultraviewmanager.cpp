#include "ultraviewmanager.h"
#include <QApplication>

UltraViewManager::closeView(IView *view)
{
    //TODO
    Q_UNUSED(view)
}

EditorView *UltraViewManager::currentEditorView()
{
    //TODO
    return m_current;
}

UltraViewManager::splitNewWindow(EditorView *ev)
{
    //TODO
    Q_UNUSED(ev)
}

void UltraViewManager::setCurrentView(EditorView *ev)
{
    //TODO
    Q_UNUSED(ev)
}

UltraViewManager::closeEditorView(EditorView *ev)
{
    //TODO
    Q_UNUSED(ev)
}

UltraViewManager::activateEditorView(EditorView *ev)
{
    //TODO
    Q_UNUSED(ev)
}

void UltraViewManager::onFocusChange(QWidget *o, QWidget *n)
{
    //TODO
    Q_UNUSED(o)
    Q_UNUSED(n)
}

UltraViewManager::UltraViewManager()
{
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), SLOT(onFocusChange(QWidget*,QWidget*)));
}
