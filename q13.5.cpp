#include <iostream>
#include <string_view>

class BallA
{
    std::string_view m_color{"black"};
    double m_radius{10.0};

    public:
        BallA() = default;
        BallA(std::string_view color) { m_color = color; }
        BallA(double rad) { m_radius = rad; }
        BallA(std::string_view color, double rad) {
            m_color = color; m_radius = rad; }
//        void setColor(std::string_view color) { m_color = color; }
//        void setRadius(double rad) { m_radius = rad; }
//        void setValues(std::string_view color, double rad) {
//            m_color = color; m_radius = rad; }
        void print() { std::cout << "color: " << m_color << ", "
                                 << "radius: " << m_radius << '\n';
        }
};

class BallB
{
    std::string_view m_color{};
    double m_radius{};

    public:
        BallB(std::string_view color = "black", double rad = 10.0) {
            m_color = color; m_radius = rad; }
        BallB(double rad) { m_radius = rad; }
        void print() { std::cout << "color: " << m_color << ", "
                                 << "radius: " << m_radius << '\n';
        }
};

int main()
{
    BallA defA{};
    defA.print();

    BallA blueA{ "blue" };
    blueA.print();

    BallA twentyA{ 20.0 };
    twentyA.print();

    BallA blueTwentyA{ "blue", 20.0 };
    blueTwentyA.print();


    BallB defB{};
    defB.print();

    BallB blueB{ "cyan" };
    blueB.print();

    BallB twentyB{ 60.0 };
    twentyB.print();

    BallB blueTwentyB{ "magenta", 66.0 };
    blueTwentyB.print();

    return 0;
}
