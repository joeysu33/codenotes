#if !defined(EDITORTOOLBAR_INCLUDED_H)
#define EDITORTOOLBAR_INCLUDED_H

#include "styledbar.h"
#include "iconprovider.h"

#include <functional>

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

//class IEditor;
//class IDocument;

struct EditorToolBarPrivate;

/**
  * Fakes an IEditor-like toolbar for design mode widgets such as Qt Designer and Bauhaus.
  * Creates a combobox for open files and lock and close buttons on the right.
  */
class EditorToolBar : public StyledBar
{
    Q_OBJECT

public:
    explicit EditorToolBar(QWidget *parent = 0);
    virtual ~EditorToolBar();

    typedef std::function<void(QMenu*)> MenuProvider;
    enum ToolbarCreationFlags { FlagsNone = 0, FlagsStandalone = 1 };

    /**
      * Adds an editor whose state is listened to, so that the toolbar can be kept up to date
      * with regards to locked status and tooltips.
      */
//    void addEditor(IEditor *editor);

    /**
      * Sets the editor and adds its custom toolbar to the widget.
      */
//    void setCurrentEditor(IEditor *editor);

//    void setToolbarCreationFlags(ToolbarCreationFlags flags);
    void setMenuProvider(const MenuProvider &provider);

    /**
      * Adds a toolbar to the widget and sets invisible by default.
      */
//    void addCenterToolBar(QWidget *toolBar);

    void setNavigationVisible(bool isVisible);
    void setCanGoBack(bool canGoBack);
    void setCanGoForward(bool canGoForward);
//    void removeToolbarForEditor(IEditor *editor);
    void setCloseSplitEnabled(bool enable);
    void setCloseSplitIcon(const QIcon &icon);

signals:
    void closeClicked();
    void goBackClicked();
    void goForwardClicked();
    void horizontalSplitClicked();
    void verticalSplitClicked();
    void splitNewWindowClicked();
    void closeSplitClicked();
    void listSelectionActivated(int row);
//    void currentDocumentMoved();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
//    void changeActiveEditor(int row);
//    void makeEditorWritable();

//    void checkDocumentStatus();
    void closeEditor();
    void updateActionShortcuts();

//    void updateDocumentStatus(IDocument *document);
//    void updateEditorListSelection(IEditor *newSelection);
//    void fillListContextMenu(QMenu *menu);
//    void updateToolBar(QWidget *toolBar);

    EditorToolBarPrivate *d;
};

#endif //EDITORTOOLBAR_INCLUDED_H
