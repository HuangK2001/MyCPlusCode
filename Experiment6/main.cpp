#include <QCoreApplication>
#include <iostream>
#include <string.h>
#include "testString.h"
#include "a.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);//����ı���a�Ѿ�ʹ�ã�����A a;�������ض������
    cout<<"����Ϊ����һ:"<<endl;
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
    (++++e).show();//�Ӹ����Ű�++++e����һ�����壬ͨ�������������
    cout<<"����Ϊ�����:"<<endl;
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
