#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
using namespace std;
//任务二（类模板）
template <class T>
class Array
{
public:
    Array(int itsSize = 4);
    Array(const Array &rhs);
    ~Array() { delete []pType; }
    Array& operator=(const Array&);
    T& operator[](int index) { return pType[index]; }
    int getSize() { return itsSize; }
private:
    T *pType;
    int itsSize;

};
//之前把模板定义放在cpp文件里，会报错
template <class T>
Array<T>::Array(int size): itsSize(size)
{
    pType = new T[size];
    for (int i = 0; i<size; i++)
        pType[i] = 0;
}
template <class T>
Array<T>::Array(const Array &rhs)
{
    itsSize = rhs.GetSize();
    pType = new T[itsSize];
    for (int i = 0; i<itsSize; i++)
        pType[i] = rhs[i];
}
template <class T>
Array<T>& Array<T>::operator=(const Array &rhs)
{
    if (this == &rhs)
        return *this;
    delete [] pType;
    itsSize = rhs.GetSize();
    pType = new T[itsSize];
    for (int i = 0; i<itsSize; i++)
        pType[i] = rhs[i];
    return *this;
}

template <class T>
void Disp( Array<T> & theArray)
{
    for(int j=0; j<theArray.getSize(); j++)
    {
        cout << theArray[j];
    }
}
#endif // ARRAY_H
