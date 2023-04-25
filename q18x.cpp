#include <iostream>
#include <ostream>

class Point
{
private:
	int m_x{};
	int m_y{};

public:
	Point(int x, int y)
		: m_x{ x }, m_y{ y }
	{

	}

	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
	}
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual std::ostream& print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Shape& sh)
    {
        return sh.print(out);
    }
};

class Triangle : public Shape
{
    Point m_p1, m_p2, m_p3;
public:
    Triangle(const Point& a, const Point& b, const Point& c)
        : m_p1{ a }, m_p2{ b }, m_p3{ c } {}
    std::ostream& print(std::ostream& out) const override
    {
        return out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')';
    }
};

class Circle : public Shape
{
    Point m_c;
    int m_radius;
public:
    Circle(const Point& c, int r) : m_c{ c }, m_radius{ r } {}
    std::ostream& print(std::ostream& out) const override
    {
        return out << "Circle(" << m_c << ", radius " << m_radius << ')';
    }
};

int main()
{
    Circle c{ Point{ 1, 2 }, 7 };
    std::cout << c << '\n';

    Triangle t{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }};
    std::cout << t << '\n';

    return 0;
}
