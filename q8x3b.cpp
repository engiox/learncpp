#include <iostream>

void print()
{
    std::cout << "void\n";
}

void print(int x=0)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

void print(double x, int y=0)
{
    std::cout << "int, double " << x << ", " << y << '\n';
}

int main()
{
    print(5.0f);
    print();

    return 0;
}
