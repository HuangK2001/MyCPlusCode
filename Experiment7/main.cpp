#include <QCoreApplication>
#include <iostream>
#include <vector>
#include "array.h"
using namespace std;
//����һ������ģ�壩
template <class T>
T Max(T a, T b)
{
    return (a > b ? a : b);
}
template <class T>
T Min(T a, T b)
{
    return (a < b ? a : b);
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "����һ(����ģ��)��" << endl;
    cout << "max(5, 2)=" << Max(5, 2) << endl;
    cout << "max(a, b)=" << Max('a', 'b') << endl;
    cout << "min(3, 4)=" << Min(3, 4) << endl;
    cout << "min(c, d)=" << Min('c', 'd') << endl;
    cout << "�����(��ģ��)��" << endl;
    Array<int> theArray;
    Array<char> theString;
    for (int i = 0; i < theArray.getSize(); i++)
    {
        theArray[i] = i * 2;
        theString[i] = 'A' + i;
    }
    Disp(theArray);
    cout << endl;
    Disp(theString);
    cout << endl;
    cout << "������(vector����)��" << endl;
    unsigned int i;
    // constructors used in the same order as described above:
    std::vector<int> first; //������
    std::vector<int> second (4,100); //����Ϊ4��100������
    std::vector<int> third (second.begin(),second.end()); //ʹ�õ������õ�second����ʼλ�ú��յ�λ�ø���third����
    std::vector<int> fourth (third); //����third������fourth
    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );
    std::cout << "The contents of fifth are:";
    for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)//��һ��ѭ�����������ֵ
        std::cout << ' ' << *it;
    std::cout << '\n';
    return a.exec();
}






