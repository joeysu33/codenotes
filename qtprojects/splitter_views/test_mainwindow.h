#ifndef TEST_MAINWINDOW_H
#define TEST_MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QPlainTextEdit>

class NGPSPViewOrSplitter;
class QToolBar;
class Test_MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit Test_MainWindow(QWidget *parent = nullptr);
    ~Test_MainWindow();
private:
    void test_addRootView();
    void test_splitCurrentViewHorizontal();
    void test_splitCurrentViewVertical();
    void test_unsplitCurrentView();
    void test_unsplitAll();
    void test_split(int direction);
private slots:
    void onSplitCurrentViewHorizontal();
    void onSplitCurrentViewVertical();
    void onSplit();
    void onUnsplitCurrentView();
    void onUnsplitAll();
private:
    NGPSPViewOrSplitter *m_sp {Q_NULLPTR};
    QToolBar *m_toolBar {Q_NULLPTR};
};

class PlainTextEdit : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit PlainTextEdit(const QString& text, QWidget *parent = Q_NULLPTR)
        :QPlainTextEdit(text,parent){
        qDebug()<<"newEdit:"<<text;
    }

    ~PlainTextEdit() {
        qDebug()<<"deleteEdit:"<<toPlainText();
    }
};


#endif // TEST_MAINWINDOW_H
