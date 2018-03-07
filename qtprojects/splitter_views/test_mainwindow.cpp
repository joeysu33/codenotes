#include "test_mainwindow.h"
#include "ngpspview.h"

#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include <QApplication>

namespace {
    static QPlainTextEdit* newEdit() {
        static int offset=0;
        QString text;
        text = QString("A-%1").arg(offset++, 3, 10, QChar('0'));
        QPlainTextEdit *editor = new PlainTextEdit(text);
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
    QList<QString> splitOpts;
    splitOpts << "left" <<"right"<<"top"<<"bottom";
    QList<int> directions;
    directions << NGPSPViewOrSplitter::SO_LEFT
               <<NGPSPViewOrSplitter::SO_RIGHT
              <<NGPSPViewOrSplitter::SO_TOP
             <<NGPSPViewOrSplitter::SO_BOTTOM;
    QList<QAction*> actions;
    QAction *act;
    for(int i=0; i<splitOpts.size(); ++i) {
        act = new QAction(QString("split-%1").arg(splitOpts[i]));
        connect(act, SIGNAL(triggered()), SLOT(onSplit()));
        act->setData(directions[i]);
        actions << act;
    }
//    act = new QAction("split vertical");
//    connect(act, SIGNAL(triggered()), SLOT(onSplitCurrentViewVertical()));
//    actions << act;
    act = new QAction("unsplit");
    connect(act, SIGNAL(triggered(bool)), SLOT(onUnsplitCurrentView()));
    actions << act;
    act = new QAction("unsplitAll");
    connect(act, SIGNAL(triggered(bool)), SLOT(onUnsplitAll()));
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
        s->split(newEdit());
    }
}

void Test_MainWindow::test_splitCurrentViewVertical()
{
    if(NGPSPViewOrSplitter *s =  currentViewOrSplitter()) {
        s->split(newEdit(), NGPSPViewOrSplitter::SO_BOTTOM);
    }
}

void Test_MainWindow::test_unsplitCurrentView()
{
    if(NGPSPViewOrSplitter *s =  currentViewOrSplitter()) {
        if(!s->isSplitter()) {
            if(NGPSPViewOrSplitter *p = s->findParentViewOrSplitter()) {
                p->unsplit(s->getView());
            }
        }
    }
}

void Test_MainWindow::test_unsplitAll()
{
    if(!m_sp->unsplitAll()) {
        qDebug()<<"unsplit All erros:"<<m_sp->getError();
    }
}

void Test_MainWindow::test_split(int direction)
{
    NGPSPViewOrSplitter *s =  currentViewOrSplitter();
    if(!s) return;
    s->split(newEdit(), (NGPSPViewOrSplitter::SplitOrientation)direction);
}

void Test_MainWindow::onSplitCurrentViewHorizontal()
{
    test_splitCurrentViewHorizontal();
}

void Test_MainWindow::onSplitCurrentViewVertical()
{
    test_splitCurrentViewVertical();
}

void Test_MainWindow::onSplit()
{
    if(QAction *a = qobject_cast<QAction*>(sender())) {
        test_split(a->data().toInt());
    }
}

void Test_MainWindow::onUnsplitCurrentView()
{
    test_unsplitCurrentView();
}

void Test_MainWindow::onUnsplitAll()
{
    test_unsplitAll();
}


