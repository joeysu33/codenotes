#ifndef ULTRAVIEWMANAGER_H
#define ULTRAVIEWMANAGER_H

/*!
 * \brief The UltraViewManager class
 * 无限分割View的管理器
 */
#include <QObject>

class EditorView;
class SplitterOrView;
class IView;

class UltraViewManager : public QObject
{
    Q_OBJECT
public:
    static UltraViewManager* instance();

    //IView operators
//    static void closeView(IView *view);
    static IView *currentView();
    static void setCurrentView(IView *view);
    static void closeView(IView* v);

    //EditorView operators
    static EditorView* currentEditorView();
    static void splitNewWindow(EditorView *ev);
    static IView* duplicateView(IView *v);
    static void emptyEditorView(EditorView*v);
    static EditorView* viewForEditor(IView *v);

    static void setCurrentEditorView(EditorView *ev);
    static EditorView *getCurrentView() ;
    static void closeEditorView(EditorView *ev);
    static void activateEditorView(EditorView *ev);
private slots:
    void onFocusChange(QWidget *o, QWidget *n);
signals:
    void currentViewAboutToChanged(IView *view);
    void currentViewChanged(IView *view);
private:
    UltraViewManager();
    Q_DISABLE_COPY(UltraViewManager)
private:
    EditorView *m_current {Q_NULLPTR};
    IView *m_currentView {Q_NULLPTR };
};

#endif // ULTRAVIEWMANAGER_H
