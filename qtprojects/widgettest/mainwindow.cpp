#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainform.h"
#include "mainform.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_mf = ui->widget;

    QList<QAction*> actions;
    actions << ui->actionFold;
    for(auto a : actions) connect(a, SIGNAL(triggered(bool)), SLOT(onTrigger()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTrigger()
{
    QAction *act = qobject_cast<QAction*>(sender());
    if(!act) return ;

    QWidget * tar {m_mf->ui->widget };
    tar->setVisible(!tar->isVisible());
}
