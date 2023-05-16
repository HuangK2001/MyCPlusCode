#include "singleton.h"
#include <iostream>
using namespace std;
Singleton::Singleton(){}                 //定义构造函数
Singleton::~Singleton()                //定义析构函数
{
    delete Instance;
}
Singleton *Singleton::Instance = NULL; //先初始化存储对象的指针为空

Singleton *Singleton::getInstance()
{
    if (NULL == Instance){
        //本函数第一次调用时，创建一个Singleton对象，对象地址由instance记录
        //该对象将一直存在直到程序结束
        Instance = new Singleton();
    }
    return Instance;
}
string Singleton::getName()       //定义getName()成员函数
{
    return name;
    //调用时返回修改后的name值
}
void Singleton::setName(string n) //定义setName()成员函数
{
    name = n;
    //使用传入的值赋给name，实现修改
}
