#ifndef A_H
#define A_H
#include <iostream>
using namespace std;

class A
{
public:
    A(int x, int y) : a(x), b(y) {}
public:
    A& operator++(); //前置++
    A operator++(int); //后置++
    void show() const
    {
        cout << "a:" << a << endl
             << "b:" << b << endl;
    }
private:
    int a;
    int b;
};

#endif // A_H
