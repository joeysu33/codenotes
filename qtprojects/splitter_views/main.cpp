#include "test_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Test_MainWindow mw;
    mw.show();
    return app.exec();
}
