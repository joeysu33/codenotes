#include <QCoreApplication>
#include <iostream>
#include "../testlib/testlib.h"

using namespace  std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TestLib tlb;
    std::cout<<"tlb.add(10,20)="<<tlb.add(10,20)<<std::endl;

    return 0;
}
