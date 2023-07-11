#include <iostream>
#include <cmath>

class Point2D
{
    double m_x, m_y;
public:
    Point2D() { m_x = 0.0, m_y = 0.0; }
    Point2D(double x, double y) { m_x = x, m_y = y; }
    void print() const { std::cout << "Point2D(" << m_x << ", " << m_y << ")\n"; }
    double distanceTo(const Point2D& dest) const {
        return std::sqrt((m_x - dest.m_x) * (m_x - dest.m_x) + (m_y - dest.m_y) * (m_y - dest.m_y));
    }
    friend double distanceFrom(const Point2D& dept, const Point2D& dest)
    {
        return std::sqrt((dept.m_x - dest.m_x) * (dept.m_x - dest.m_x)
                + (dept.m_y - dest.m_y) * (dept.m_y - dest.m_y));
    }
};

int main()
{
    Point2D first{};
    Point2D second{ 3.0, 4.0 };

    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';
    std::cout << "Distance between two points: " << distanceFrom(first, second) << '\n';

    return 0;
}
