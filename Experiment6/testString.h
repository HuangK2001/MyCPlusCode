#ifndef STRING_H
#define STRING_H
#include <iostream>
using namespace std;

class String
{
public: //ctor & dtor
    String();
    String(const char* str);
    ~String();
public: //copy ctor
    String(const String &other);
public: //assign operator
    String& operator=(const String &copy);
public: //interface
    void show() const
    {
        cout << m_nLen << endl
             << m_pStr << endl;
    }
private:
    char* m_pStr;
    unsigned int m_nLen;
};

#endif // STRING_H
