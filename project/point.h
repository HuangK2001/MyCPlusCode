#ifndef POINT_H
#define POINT_H
#include <iostream>
using namespace std;

class point
{
public:
    point(int nX = 0,int nY = 0);
    int GetX() const;
    void SetX(const int& nX);
    int GetY() const;
    void SetY(const int& nY);
private:
    int m_nX;
    int m_nY;
};

#endif // POINT_H
