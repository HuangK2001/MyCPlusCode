#include "employee.h"
#include <cstring>
#include <iostream>
using namespace std;
Employee::Employee(char * s1, char * s2)
{
    int nLen = strlen(s1);
    name = new char[nLen + 1];
    memset(name,'\0',nLen + 1);
    memcpy(name,s1,nLen);//深拷贝

    nLen = strlen(s2);
    post = new char[nLen + 1];
    memset(post,'\0',nLen + 1);
    memcpy(post,s2,nLen);//深拷贝
}
// 拷贝构造函数
Employee::Employee(const Employee &other)
{
    int nLen = strlen(other.name);
    name = new char[nLen + 1];
    memset(name,'\0',nLen + 1);
    memcpy(name,other.name,nLen);

    nLen = strlen(other.post);
    post = new char[nLen + 1];
    memset(post,'\0',nLen + 1);
    memcpy(post,other.post,nLen);
}
// 以下四个为针对姓名和职务的set/get函数
void Employee::setName(char * str)
{
    if(name != NULL)
    {
        delete []name;
        name = NULL;
    }
    int nLen = strlen(str);
    name = new char[nLen + 1];
    memset(name,'\0',nLen + 1);
    memcpy(name,str,nLen);
}
void Employee::setPost(char * str)
{
    if(post != NULL)
    {
        delete []post;
        post = NULL;
    }
    int nLen = strlen(str);
    post = new char[nLen + 1];
    memset(post,'\0',nLen + 1);
    memcpy(post,str,nLen);
}

