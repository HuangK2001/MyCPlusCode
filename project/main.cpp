#include <QCoreApplication>
#include "point.h"
void printPoint(const point& p)
{
    cout << "["
         <<p.GetX()
         <<","
         <<p.GetY()
         <<"]"
         <<endl;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    point p(2,3);
    printPoint(p);
    return a.exec();
}
