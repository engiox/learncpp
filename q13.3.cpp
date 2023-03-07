#include <iostream>
#include <cassert>

class Point3d
{
    int m_x{}, m_y{}, m_z{};
public:
    void SetValues(int v1, int v2, int v3)
        { m_x = v1; m_y = v2; m_z = v3; }
    void print()
        { std::cout << '<' << m_x << ", " << m_y << ", " << m_z << '>'; }
    bool isEqual(const Point3d &pt) 
        { return (m_x == pt.m_x && m_y == pt.m_y && m_z == pt.m_z); }
};

class Stack
{
    static constexpr int max_num{ 10 };
    int values[max_num];
    int size{0};

    public:
    void reset() { size = 0; }
    bool push(int val) { if (size >=max_num) return false;
        values[size] = val; ++size; return true; }
    int pop() { assert(size > 0 && "Empty stack\n");
                --size; return values[size]; } 
    void print() { std::cout << "( ";
                   for (int i{0}; i < size; ++i) {
                       std::cout << values[i] << ' ';
                   }
                   std::cout << ")\n"; }
};

void q2a()
{
    Point3d point;
    point.SetValues(1, 2, 3);

    point.print();
    std::cout << '\n';
}

void q2b()
{
    Point3d point1;
    point1.SetValues(1, 2, 3);

    Point3d point2;
    point2.SetValues(1, 2, 3);

    if (point1.isEqual(point2)) {
        std::cout << "point1 and point2 are equal\n";
    } else {
        std::cout << "point1 and point2 are not equal\n";
    }

    Point3d point3;
    point3.SetValues(3, 4, 5);

    if (point1.isEqual(point3)) {
        std::cout << "point1 and point3 are equal\n";
    } else {
        std::cout << "point1 and point3 are not equal\n";
    }
}

void q3()
{
    Stack stk;
    stk.print();

    stk.push(5);
    stk.push(3);
    stk.push(8);
    stk.print();

    stk.pop();
    stk.print();

    stk.pop();
    stk.pop();

    stk.print();
}

int main()
{
    q2a();
    q2b();
    q3();
    return 0;
}
