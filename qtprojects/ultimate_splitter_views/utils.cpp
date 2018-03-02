#include "utils.h"
#include <QDebug>

Utils::Utils()
{

}

void Utils::writeAssertLocation(const char *msg)
{
    qDebug("SOFT ASSERT: %s", msg);
}
