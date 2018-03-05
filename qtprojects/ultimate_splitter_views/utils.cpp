#include "utils.h"
#include <QDebug>
#include <QWidget>

Utils::Utils()
{

}

void Utils::writeAssertLocation(const char *msg)
{
    qDebug("SOFT ASSERT: %s", msg);
}

void Utils::raiseWindow(QWidget * widget)
{
    if(!widget) return ;
   if(QWidget *window = widget->window()) {
        window->raise();
        window->activateWindow();
    }
}
