#include "test_mainwindow.h"
#include "ngpspview.h"

#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include <QApplication>
#include <QPlainTextEdit>

namespace {
    static QPlainTextEdit* newEdit() {
        static const char c('A');
        static int offset=0;
        QPlainTextEdit *editor = new QPlainTextEdit();
        QString text;
        text.fill(QChar(c + offset), 10);
        editor->setPlainText(text);
        return editor;
    }

    static NGPSPViewOrSplitter* currentViewOrSplitter() {
        NGPSPViewOrSplitter *r {Q_NULLPTR};
        QWidget *fw = qApp->focusWidget();
        while(fw) {
            if(r = qobject_cast<NGPSPViewOrSplitter*>(fw)) {
                return r;
            }
            fw = fw->parentWidget();
        }

        return Q_NULLPTR;
    }
}

Test_MainWindow::Test_MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QList<QAction*> actions;
    QAction *act;
    act = new QAction("split horizontal");
    connect(act, SIGNAL(triggered()), SLOT(onSplitCurrentViewHorizontal()));
    actions << act;
    act = new QAction("split vertical");
    connect(act, SIGNAL(triggered()), SLOT(onSplitCurrentViewVertical()));
    actions << act;
    act = new QAction("unsplit");
    connect(act, SIGNAL(triggered(bool)), SLOT(onUnsplitCurrentView()));
    actions << act;

    m_toolBar = new QToolBar();
    m_toolBar->addActions(actions);
    addToolBar(m_toolBar);

    test_addRootView();
}

Test_MainWindow::~Test_MainWindow()
{
    delete m_sp;
}

void Test_MainWindow::test_addRootView()
{
    m_sp = new NGPSPViewOrSplitter(newEdit());
    setCentralWidget(m_sp);
}

void Test_MainWindow::test_splitCurrentViewHorizontal()
{
    if(NGPSPViewOrSplitter *s =  currentViewOrSplitter()) {
        s->add(newEdit());
    }
}

void Test_MainWindow::test_splitCurrentViewVertical()
{
    if(NGPSPViewOrSplitter *s =  currentViewOrSplitter()) {
        s->add(newEdit(), NGPSPViewOrSplitter::SO_BOTTOM);
    }
}

void Test_MainWindow::test_unsplitCurrentView()
{
    if(NGPSPViewOrSplitter *s =  currentViewOrSplitter()) {
        if(!s->isSplitter()) {
            if(NGPSPViewOrSplitter *p = s->findParentViewOrSplitter()) {
                p->remove(s->getView());
            }
        }
    }
}

void Test_MainWindow::onSplitCurrentViewHorizontal()
{
    test_splitCurrentViewHorizontal();
}

void Test_MainWindow::onSplitCurrentViewVertical()
{
    test_splitCurrentViewVertical();
}

void Test_MainWindow::onUnsplitCurrentView()
{
    test_unsplitCurrentView();
}




