#include <iostream>

class Point
{
    double m_x{0};
    double m_y{0};
    double m_z{0};
public:
    Point(double x, double y, double z) : m_x{x}, m_y{y}, m_z{z} {}
    void print() {
        std::cout << "Point(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};
