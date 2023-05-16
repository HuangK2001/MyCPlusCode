#include <QCoreApplication>
#include "employee.h"
#include <iostream>
#include <string>
using namespace std;
void printEmployee(const Employee & e);
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Employee people("ZhangSan","GongChengShi");
    printEmployee(people);
    return a.exec();
}
void printEmployee(const Employee & e)
{
    cout << "["
         <<e.getName()
         << ":"
         << e.getPost()
         <<"]"
         << endl;
}
