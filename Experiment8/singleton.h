#ifndef SINGLETON_H
#define SINGLETON_H
#include <string>
using namespace std;
class Singleton
{
public:
    static Singleton *getInstance(); //该函数用于初始化一个唯一的实例
    string getName();
    void setName(string n);
private:
    Singleton();
    virtual ~Singleton();
    static Singleton *Instance; //存储对象的地址，直到程序结束
    string name; //用的string类型，char一大堆错误
};

#endif // SINGLETON_H
