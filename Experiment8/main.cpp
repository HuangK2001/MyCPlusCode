#include <QCoreApplication>
#include "singleton.h"
#include <iostream>
using namespace std;
void fun()
{
    Singleton *s = Singleton::getInstance();
    s->setName("张三");
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Singleton * t = Singleton::getInstance();
    t->setName("李四");
    //cout << t->getName() << endl; //测试实例t的修改内容
    fun(); //调用 fun（），改变name的值
    cout << t->getName() << endl;
    return a.exec();
}
