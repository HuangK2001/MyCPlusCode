#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;

class Base
{
public:
    Base(){}
    void print(int x)
    {
        cout<<"Base::print(int x)"<<x<<endl;
    }
    void print(float x)
    {
        cout<<"Base::print(float x)"<<x<<endl;
    }
    virtual void virtualPrint(void)//虚函数参数，返回值在重写时必须一样
    {
        cout<<"Base::virtualPrint(void)"<<endl;
    }
};

#endif // BASE_H
