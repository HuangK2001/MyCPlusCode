#include "point.h"

point::point(int nX, int nY):m_nX(nX),m_nY(nY)//nX的值赋给m_nX,nY的值赋给m_nY
{

}
int point::GetX() const
{
    return m_nX;
}
void point::SetX(const int& nX)
{
    m_nX = nX;
}
int point::GetY() const
{
    return m_nY;
}
void point::SetY(const int& nY)
{
    m_nY = nY;
}
