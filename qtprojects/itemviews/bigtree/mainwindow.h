#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class TreeModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void indexEnter(const QModelIndex& );
    void fetchMore(int );
private:
    Ui::MainWindow *ui;
    TreeModel *m_model {Q_NULLPTR};
};

#endif // MAINWINDOW_H
