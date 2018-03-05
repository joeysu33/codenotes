#ifndef UTILS_H
#define UTILS_H

class QWidget;
class Utils
{
public:
    Utils();

    static void writeAssertLocation(const char *msg);
    static void raiseWindow(QWidget *w);
};

#endif // UTILS_H
