#if !defined(_MAINWINDOW_INCLUDED_H)
#define _MAINWINDOW_INCLUDED_H

#include <QMainWindow>

class QWidget;
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = Q_NULLPTR);
private:
    QWidget *m_center {Q_NULLPTR };
};


#endif //_MAINWINDOW_INCLUDED_H
