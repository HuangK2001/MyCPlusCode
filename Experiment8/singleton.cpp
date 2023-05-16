#include "singleton.h"
#include <iostream>
using namespace std;
Singleton::Singleton(){}                 //���幹�캯��
Singleton::~Singleton()                //������������
{
    delete Instance;
}
Singleton *Singleton::Instance = NULL; //�ȳ�ʼ���洢�����ָ��Ϊ��

Singleton *Singleton::getInstance()
{
    if (NULL == Instance){
        //��������һ�ε���ʱ������һ��Singleton���󣬶����ַ��instance��¼
        //�ö���һֱ����ֱ���������
        Instance = new Singleton();
    }
    return Instance;
}
string Singleton::getName()       //����getName()��Ա����
{
    return name;
    //����ʱ�����޸ĺ��nameֵ
}
void Singleton::setName(string n) //����setName()��Ա����
{
    name = n;
    //ʹ�ô����ֵ����name��ʵ���޸�
}
