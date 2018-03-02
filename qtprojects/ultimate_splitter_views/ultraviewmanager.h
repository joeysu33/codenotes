#ifndef ULTRAVIEWMANAGER_H
#define ULTRAVIEWMANAGER_H

/*!
 * \brief The UltraViewManager class
 * 无限分割View的管理器
 */
#include <QObject>

class EditorView;
class IView;

class UltraViewManager : public QObject
{
    Q_OBJECT
public:
    static UltraViewManager* instance();
    //IView operators
    static closeView(IView *view);

    //EditorView operators
    static EditorView* currentEditorView();
    static splitNewWindow(EditorView *ev);
private:
    void setCurrentView(EditorView *ev);
    static closeEditorView(EditorView *ev);
    static activateEditorView(EditorView *ev);
private slots:
    void onFocusChange(QWidget *o, QWidget *n);
private:
    friend class EditorView;
    UltraViewManager();
    Q_DISABLE_COPY(UltraViewManager)
private:
    EditorView *m_current {Q_NULLPTR};
};

#endif // ULTRAVIEWMANAGER_H
