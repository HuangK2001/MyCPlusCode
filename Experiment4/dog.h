#ifndef DOG_H
#define DOG_H
#include "mammal.h"
#include <iostream>
using namespace std;
class Dog : public Mammal
{
public:
    Dog() { cout << "Dog Constructor...\n"; }
    virtual ~Dog() { cout << "Dog destructor...\n"; }
public:
    void WagTail()const { cout << "Dog Wagging Tail...\n"; }
    void Speak()const { cout << "Woof!\n"; }//重写虚函数Speak
    void Move()const { cout << "Dog moves 5 steps...\n"; }
private:
    int itsGender;
};

#endif // DOG_H
