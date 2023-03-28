#ifndef _POINT2D_H_
#define _POINT2D_H_

#include <iostream>

class Point2D
{
    int m_x;
    int m_y;

public:
    Point2D() : m_x{ 0 }, m_y { 0 }
    {}

    Point2D(int x, int y) : m_x{ x }, m_y { y }
    {}

    friend std::ostream& operator<<(std::ostream& out, const Point2D& point)
    {
        out << '(' << point.m_x << ", " << point.m_y << ')';
        return out;
    }

    void setPoint(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
};

#endif
