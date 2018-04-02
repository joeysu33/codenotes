#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainForm;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onTrigger();
private:
    Ui::MainWindow *ui;
    MainForm *m_mf {nullptr};
};

#endif // MAINWINDOW_H
