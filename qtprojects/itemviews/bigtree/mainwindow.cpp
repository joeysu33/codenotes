#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treemodel.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model = new TreeModel();
    ui->treeView->setModel(m_model);

    ui->treeView->setMouseTracking(true);
    connect(ui->treeView, SIGNAL(entered(const QModelIndex&)),
            this, SLOT(indexEnter(const QModelIndex&)) );
    connect(m_model, SIGNAL(loadMore(int)), SLOT(fetchMore(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::indexEnter(const QModelIndex & index)
{
    qDebug()<<"IndexEnter"<<"("<<index.row()<<","<<index.column()<<")";

    QModelIndex pindex = m_model->parent(index);
    if(m_model->rowCount(pindex) - index.row() < VISUALCACHE) {
        m_model->cacheMore(pindex);
    }
}

void MainWindow::fetchMore(int count)
{
    qDebug()<<"fetchmore:"<<count;
}
