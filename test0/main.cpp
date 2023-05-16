#include <QCoreApplication>
#include<iostream>//输入输出流文件库
#include<iomanip>//格式化输出头文件
using namespace std;
//命名空间,可以解决命名冲突的的问题，std指的是标准命名空间
namespace NS_test
{
    int nA = 1;
}

namespace NS_try
{
    int nA = 2;
}
using namespace NS_try;
//void add(int x,int y=1,int z=2); //如果有函数声明，则默认参数只能出现在声明中
//重载函数应避免有默认参数，否则会有二义性错误
void add(int x,int y=1,int z=2)//带有默认参数的函数。第一个默认参数后必须全是默认参数
{
    cout<<x+y+z<<endl;
}
int main(int argc, char *argv[])
{
    add(1);
    add(2,3);
    add(3,4,5);
    QCoreApplication a(argc, argv);
    //int nA = 0;
    int nB = 16;
    int &B = nB;//变量引用,引用的别名地址和原变量一致
    const int &C = 10;//常引用
    cout<<"nB address:"<<hex<<&nB<<endl;
    cout<<"B address:"<<hex<<&B<<endl;
    cout<<"B:"<<B<<endl;
//    const int nC = 10;//const表示为常变量，不可修改
    //cin >> nA >> nB;//输入流
    //cout << NS_test::nA;//指定使用命名空间里的变量
//    cout << nA << endl;
//    cout<<"oct:"<<oct<<nB<<endl;
//    cout<<"dec:"<<dec<<nB<<endl;
//    cout<<"hex:"<<hex<<nB<<endl;
//    cout<<setw(10)<<3.1415<<endl;//设置输出宽度
//    cout<<setw(10)<<setfill('0')<<3.1415<<endl;//在指定宽度的基础上设置填充
//    cout<<setw(10)<<setfill('0')<<setiosflags(ios::left)<<3.1415<<endl;//左对齐，用零填充
//    cout<<setw(10)<<setfill('-')<<setiosflags(ios::right)<<3.1415<<endl;//右对齐，用-填充
    //    宽度      填充           对齐
//    if(nA == nB)
//    {
//        cout << "dengyu" << endl;//输出流
//    }
//    else if(nA > nB)
//    {
//        cout << "dayu" << endl;
//    }
//    else
//    {
//        cout << "xiaoyu" << endl;
//    }
    return a.exec();
}
