#include <QApplication>
#include <QWidget>
#include <QWindow>
#include <iostream>
#include <QMainWindow>
#include <cstdio>
#include <QHBoxLayout>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication app(argc,argv);

    if(argc < 2) {
        cout<<"please input WID to wrapper a window (QT)"<<endl;
        return 1;
    }
    
    int wid = atoi(argv[1]);
    cout<<"wid="<<wid<<endl;

    QMainWindow mw;
    QWidget *c = new QWidget();
    c->setStyleSheet("background-color:lightsteelblue");
    QHBoxLayout * hb = new QHBoxLayout(c);

    mw.setCentralWidget(c);
    QWindow *win = QWindow::fromWinId(wid);
    QWidget *tar = QWidget::createWindowContainer(win);
    
    hb->addWidget(tar);
    mw.show();
    
    return  app.exec();
}

