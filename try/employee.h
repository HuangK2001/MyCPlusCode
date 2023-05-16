#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>
class Employee
{
private:
    char * name; // 姓名
    char * post; // 职务
public:
    // 构造函数，职务可以为空，姓名不能为空
    Employee(char * s1, char * s2 = NULL); // L1行
    // 拷贝构造函数
    Employee(const Employee & other);
    // 以下四个为针对姓名和职务的set/get函数
    void setName(char * str);
    void setPost(char * str);
    char * getName() const {return name;}
    char * getPost() const {return post;}
    // 析构函数
    ~Employee()
    {
        if(name != NULL)
        {
            delete []name;
            name = NULL;
        }
        if(post != NULL)
        {
            delete [] post;
            post = NULL;
        }
    }
};

#endif // EMPLOYEE_H
