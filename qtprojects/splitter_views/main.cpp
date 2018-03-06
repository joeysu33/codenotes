#include "test_mainwindow.h"
#include "ngpspview.h"

#include <QApplication>
#include <QPlainTextEdit>

int main(int argc, char *argv[]) {
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
