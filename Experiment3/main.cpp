#include <QCoreApplication>
#include <iostream>
#include "base.h"
#include "derive.h"
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Derive d;//不传实参，输出默认值
    d.print();
    Derive c(2,3);//传入实参，输出实参值
    c.print();
    Base b( 6 );//必须传入实参
    b.print();
    return a.exec();
}
