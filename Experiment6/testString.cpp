#include "testString.h"
#include <string.h>
using namespace std;

String::~String()
{
    m_nLen = 0;
    delete []m_pStr;
    m_pStr = NULL;
}
//拷贝构造函数
String::String(const String &copy)
{
    // 允许操作other的私有成员m_data
    int len = strlen(copy.m_pStr);
    m_pStr = new char[len+1];
    strcpy(m_pStr, copy.m_pStr);
    m_nLen = len;
}
String::String()
{
    m_nLen = 0;
    m_pStr = NULL;
}
String::String(const char* str)
{
    int len = strlen(str);
    m_pStr = new char[len+1];
    strcpy(m_pStr,str);
    m_nLen = len;
}
//赋值函数
String& String::operator=(const String &other)
{
    //(1)检查自赋值
    if(m_pStr != NULL)
    {
        //(2)释放原有的内存资源
        delete []m_pStr;
        m_pStr = NULL;
    }
    if(m_nLen != NULL)
    {
        //(2)释放原有的内存资源
        m_nLen = NULL;
    }
    //(3)分配新的内存资源, 并复制内容
    m_nLen = strlen(other.m_pStr);
    m_pStr = new char[other.m_nLen+1];
    strcpy(m_pStr,other.m_pStr);
    //(4)返回本对象的引用
    return *this;
}
