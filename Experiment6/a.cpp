#include "a.h"

A& A::operator++( )//前置++重载
{
    a++;
    b++;
    return *this;
}
A A::operator++(int)//后置++重载
{
    A temp = *this;
    a++;
    b++;
    return temp;
}
