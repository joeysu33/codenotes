#include "mainwindow.h"
#include "editorview.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent) {
    m_center= new QWidget(this);
    setCentralWidget(m_center);

    QHBoxLayout *hl = new QHBoxLayout(m_center);
    hl->setMargin(0);
    m_center->setLayout(hl);
    hl->addWidget(new SplitterOrView());
}

