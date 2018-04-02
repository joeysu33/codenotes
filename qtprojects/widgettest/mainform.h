#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

protected:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    friend class MainWindow;
    Ui::MainForm *ui;
};

#endif // MAINFORM_H
