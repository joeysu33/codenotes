#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QWebEngineScript>
#include <QWebEngineSettings>
#include <QTextEdit>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_view = ui->widget_2;
    m_url = ui->lineEdit;
    m_view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled,true);
    QObject::connect(m_url, &QLineEdit::returnPressed, [&]() -> void{
        m_view->load(QUrl::fromUserInput(m_url->text()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
