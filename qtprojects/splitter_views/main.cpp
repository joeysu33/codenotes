#include "test_mainwindow.h"
#include "ngpspview.h"

#include <QDebug>
#include <QApplication>
#include <QPlainTextEdit>

int main(int argc, char *argv[]) {
//    int offset=0;
//    QString text;
//    text = QString("A-%1").arg(offset++,3, 10, '0');
//    qDebug()<<text;
//    return 0;

    QApplication app(argc, argv);
    Test_MainWindow mw;
    mw.show();

//    QString text="NGPSPViewOrSplitter";
//    QPlainTextEdit *editor = new QPlainTextEdit();
//    editor->setPlainText(text);
//    NGPSPViewOrSplitter sp(editor);
//    sp.show();

    return app.exec();
}
