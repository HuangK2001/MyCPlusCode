#ifndef BASE_H
#define BASE_H
#include <iostream>
using namespace std;
class Base
{
public:
    Base(int a):a(a) { } //不带默认值的带参构造函数，所以创建对象时必须传入实参
public:  //protected访问权限无法类外访问
    void print()
    {
        cout << "a=" << a << endl;
    }
private:
    int a;
};


#endif // BASE_H
