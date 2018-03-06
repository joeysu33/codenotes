#ifndef TEST_MAINWINDOW_H
#define TEST_MAINWINDOW_H

#include <QMainWindow>

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
private slots:
    void onSplitCurrentViewHorizontal();
    void onSplitCurrentViewVertical();
    void onUnsplitCurrentView();
private:
    NGPSPViewOrSplitter *m_sp {Q_NULLPTR};
    QToolBar *m_toolBar {Q_NULLPTR};
};

#endif // TEST_MAINWINDOW_H
