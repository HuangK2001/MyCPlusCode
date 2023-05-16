#ifndef MAMMAL_H
#define MAMMAL_H
#include <iostream>
using namespace std;
class Mammal
{
public:
    Mammal():itsAge(1) { cout << "Mammal constructor...\n"; }
    virtual ~Mammal() { cout << "Mammal destructor...\n"; }
public:
    void Move()const { cout << "Mammal move one step\n"; }
    //Move不是虚函数，所以即使指针对象重写了函数Move，也还是输出本类中的内容
    virtual void Speak() const { cout << "Mammal speak!\n"; }
    //Speak是个虚函数，所以输出的内容是指针指向的对象重写的函数Speak，否则输出本类中的内容
    void WagTail()const { cout << "Mammal Wagging Tail...\n"; }
    //WagTail不是虚函数，所以即使指针对象重写了函数WagTail，也还是输出本类中的内容
private:
    int itsAge;
};
#endif // MAMMAL_H
