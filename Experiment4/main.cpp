#include <QCoreApplication>
#include "mammal.h"
#include "dog.h"
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mammal *pDog = new Dog;
    pDog->Move();
    pDog->Speak();
    pDog->WagTail();
    delete pDog;
    pDog = NULL;
    return a.exec();
}
