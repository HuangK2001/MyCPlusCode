#include <QCoreApplication>
#include <iostream>
#include"base.h"
#include"derive.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Derive d;
    Base *pb = &d;
    Derive *pd = &d;
    pb->print(3);//[13和14]或[15和16]行,如果基类和派生类有同名函数，
    pd->print(3);//则依据类指针调用相应类的成员函数，体现成员函数的隐藏
    pb->print(3.1415f);
    pd->print(3.1415f);//[13和15]或[14和16]行体现了成员函数重载。
    pb->virtualPrint();//17和18行，当成员函数声明为虚函数时，无论是哪个对象指针调用，都只调用派生类的。
    pd->virtualPrint();//体现了成员函数的覆盖。
    return a.exec();
}
