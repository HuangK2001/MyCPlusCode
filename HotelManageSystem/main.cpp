#include<QCoreApplication>
#include<room.h>
#include<iostream>
#include<time.h>
#include<room_manage.h>
#include<view.h>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Romm_view grv;
    grv.run();
    return a.exec();
}
