#ifndef DERIVE_H
#define DERIVE_H
#include "base.h"//用户自定义头文件，用双引号
#include <iostream>
using namespace std;
class Derive : public Base
{
public:
    //添加一个带默认参数的带参构造函数，创建对象时可不传入实参
    Derive(int x = 0,int y = 0):Base(x),b(y)
    {

    }
    void print()
    {
        Base::print();
        cout << "b=" << b << endl;
    }
private:
    int b;
};

#endif // DERIVE_H
