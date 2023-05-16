#include <QCoreApplication>
#include "singleton.h"
#include <iostream>
using namespace std;
void fun()
{
    Singleton *s = Singleton::getInstance();
    s->setName("����");
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Singleton * t = Singleton::getInstance();
    t->setName("����");
    //cout << t->getName() << endl; //����ʵ��t���޸�����
    fun(); //���� fun�������ı�name��ֵ
    cout << t->getName() << endl;
    return a.exec();
}
