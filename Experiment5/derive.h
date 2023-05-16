#ifndef DERIVE_H
#define DERIVE_H
#include <iostream>
#include "base.h"
using namespace std;

class Derive:public Base
{
public:
    Derive(){}
    void print(int x)//派生类的同名函数参数类型可以与基类相同也可不同。
    {
        cout<<"Derive::print(int x) "<<x<<endl;
    }
    void print(float x)
    {
        cout<<"Derive::print(float x) "<<x<<endl;
    }
    virtual void virtualPrint(void)
    {
        cout<<"Derive::virtualPrint(void)"<<endl;
    }
};

#endif // DERIVE_H
