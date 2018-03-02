#if !defined(_EDITOR_VIEW_INCLUDED_H)
#define _EDITOR_VIEW_INCLUDED_H

//#include "coreplugin/id.h"
//#include <utils/dropsupport.h>

#include <QMap>
#include <QList>
#include <QString>
#include <QPointer>
#include <QVariant>

#include <QIcon>
#include <QWidget>

#include <functional>

QT_BEGIN_NAMESPACE
class QAction;
class QComboBox;
class QFrame;
class QLabel;
class QMenu;
class QSplitter;
class QStackedLayout;
class QStackedWidget;
class QToolButton;
QT_END_NAMESPACE

class IView;
class EditorToolBar;
//class IContext;
//class IDocument;
//class IView;
//class InfoBarDisplay;
//class DocumentModel;
//class EditorToolBar;

//struct EditLocation {
//    QPointer<IDocument> document;
//    QString fileName;
//    Id id;
//    QVariant state;
//};

class SplitterOrView;

class EditorView : public QWidget
{
    Q_OBJECT

public:
    explicit EditorView(SplitterOrView *parentSplitterOrView, QWidget *parent = 0);
    virtual ~EditorView();

    SplitterOrView *parentSplitterOrView() const;
    EditorView *findNextView();
    EditorView *findPreviousView();

    int editorCount() const;
    void addEditor(IView *editor);
    void removeEditor(IView *editor);
    IView *currentEditor() const;
    void setCurrentEditor(IView *editor);

    bool hasEditor(IView *editor) const;

    QList<IView *> editors() const;
//    IView *editorForDocument(const IDocument *document) const;

    void showEditorStatusBar(const QString &id,
                           const QString &infoText,
                           const QString &buttonText,
                           QObject *object, const std::function<void()> &function);
    void hideEditorStatusBar(const QString &id);
    void setCloseSplitEnabled(bool enable);
    void setCloseSplitIcon(const QIcon &icon);

//    static void updateEditorHistory(IView *editor, QList<EditLocation> &history);

signals:
    void currentEditorChanged(IView *editor);

protected:
//    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void focusInEvent(QFocusEvent *);

private:
    friend class SplitterOrView; // for setParentSplitterOrView

    void closeCurrentEditor();
    void listSelectionActivated(int index);
    void splitHorizontally();
    void splitVertically();
    void splitNewWindow();
    void closeSplit();
//    void openDroppedFiles(const QList<Utils::DropSupport::FileSpec> &files);

    void setParentSplitterOrView(SplitterOrView *splitterOrView);

    void fillListContextMenu(QMenu *menu);
//    void updateNavigatorActions();
    void updateToolBar(IView *editor);
    void checkProjectLoaded(IView *editor);

    SplitterOrView *m_parentSplitterOrView;
    EditorToolBar *m_toolBar;

    QStackedWidget *m_container;
//    InfoBarDisplay *m_infoBarDisplay;
    QString m_statusWidgetId;
    QFrame *m_statusHLine;
    QFrame *m_statusWidget;
    QLabel *m_statusWidgetLabel;
    QToolButton *m_statusWidgetButton;
    QList<IView *> m_editors;
    QMap<QWidget *, IView *> m_widgetEditorMap;
    QLabel *m_emptyViewLabel;

//    QList<EditLocation> m_navigationHistory;
//    QList<EditLocation> m_editorHistory;
//    int m_currentNavigationHistoryPosition;
//    void updateCurrentPositionInNavigationHistory();

//public:
//    inline bool canGoForward() const { return m_currentNavigationHistoryPosition < m_navigationHistory.size()-1; }
//    inline bool canGoBack() const { return m_currentNavigationHistoryPosition > 0; }

//public slots:
    void goBackInNavigationHistory();
    void goForwardInNavigationHistory();

//public:
//    void addCurrentPositionToNavigationHistory(const QByteArray &saveState = QByteArray());
//    void cutForwardNavigationHistory();

//    inline QList<EditLocation> editorHistory() const { return m_editorHistory; }

//    void copyNavigationHistoryFrom(EditorView* other);
//    void updateEditorHistory(IView *editor);
};

class SplitterOrView  : public QWidget
{
    Q_OBJECT
public:
    explicit SplitterOrView(IView *editor = 0);
    explicit SplitterOrView(EditorView *view);
    ~SplitterOrView();

    void split(Qt::Orientation orientation);
    void unsplit();

    inline bool isView() const { return m_view != 0; }
    inline bool isSplitter() const { return m_splitter != 0; }

    inline IView *editor() const { return m_view ? m_view->currentEditor() : 0; }
    inline QList<IView *> editors() const { return m_view ? m_view->editors() : QList<IView*>(); }
    inline bool hasEditor(IView *editor) const { return m_view && m_view->hasEditor(editor); }
    inline bool hasEditors() const { return m_view && m_view->editorCount() != 0; }
    inline EditorView *view() const { return m_view; }
    inline QSplitter *splitter() const { return m_splitter; }
    QSplitter *takeSplitter();
    EditorView *takeView();

    QByteArray saveState() const;
    void restoreState(const QByteArray &);

    EditorView *findFirstView();
    EditorView *findLastView();
    SplitterOrView *findParentSplitter() const;

    QSize sizeHint() const { return minimumSizeHint(); }
    QSize minimumSizeHint() const;

    void unsplitAll();

signals:
    void splitStateChanged();

private:
    void unsplitAll_helper();
    QStackedLayout *m_layout;
    EditorView *m_view;
    QSplitter *m_splitter;
};

#endif //_EDITOR_VIEW_INCLUDED_H
