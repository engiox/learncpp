#include <iostream>

int add(int x, int y)
{
    std::cout << "int ver.\n";
    return x + y;
}

double add(double x, double y)
{
    std::cout << "double ver.\n";
    return x + y;
}

int main()
{
    std::cout << add(1, 2) << '\n';
    std::cout << add(1.2, 3.4) << '\n';
    std::cout << add(1, 2.3);
    std::cout << add(1.2, 3);

    return 0;
}
