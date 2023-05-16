#include <QCoreApplication>
#include <iostream>
#include <string.h>
#include "testString.h"
#include "a.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);//这里的变量a已经使用，所以A a;会引发重定义错误
    cout<<"以下为任务一:"<<endl;
    cout<<"d++++.show():"<<endl;
    A d(1,4);
    d++++.show();
    cout<<"b++++.show():"<<endl;
    A b(2,5);
    b++++.show();
    cout<<"(++c)++.show():"<<endl;
    A c(3,6);
    (++c)++.show();
    cout<<"++++c.show():"<<endl;
    A e(4,5);
    (++++e).show();//加个括号把++++e当作一个整体，通过对象调用重载
    cout<<"以下为任务二:"<<endl;
    String s1 = "abcd";
    String s2 = "xyz";
    String s3 = s1;
    String s4 = s2;
    cout<<"s1.show():"<<endl;
    s1.show();
    cout<<"s2.show():"<<endl;
    s2.show();
    cout<<"s3.show():"<<endl;
    s3.show();
    cout<<"s4.show():"<<endl;
    s4.show();
    cout<<"s3=s2,s4=s1:"<<endl;
    s3 = s2;
    s4 = s1;
    cout<<"s3.show():"<<endl;
    s3.show();
    cout<<"s4.show():"<<endl;
    s4.show();
    return a.exec();
}
