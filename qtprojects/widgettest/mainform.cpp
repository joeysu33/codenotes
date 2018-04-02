#include "mainform.h"
#include "ui_mainform.h"
#include <QMouseEvent>
#include <QDebug>

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    ui->tableWidget->installEventFilter(this);
}

MainForm::~MainForm()
{
    delete ui;
}

bool MainForm::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    qDebug()<<"event-type:"<<event->type();
    if(QMouseEvent *me = dynamic_cast<QMouseEvent*>(event)) {
        if(me->button() == Qt::LeftButton) {
            qDebug()<<"leftbutton:";
        } else if (me->button() == Qt::RightButton) {
            qDebug()<<"rightbutton";
        }
    }

    return false;
}
