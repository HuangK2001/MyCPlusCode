#ifndef SINGLETON_H
#define SINGLETON_H
#include <string>
using namespace std;
class Singleton
{
public:
    static Singleton *getInstance(); //�ú������ڳ�ʼ��һ��Ψһ��ʵ��
    string getName();
    void setName(string n);
private:
    Singleton();
    virtual ~Singleton();
    static Singleton *Instance; //�洢����ĵ�ַ��ֱ���������
    string name; //�õ�string���ͣ�charһ��Ѵ���
};

#endif // SINGLETON_H
