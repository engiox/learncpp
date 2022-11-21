#include <iostream>

int main()
{
    std::cout << 5;
    std::cout << 5L;

    unsigned int x { 5u };
    std::cout << x;

    x = 5;
    std::cout << x;

    double avogadro { 6.02e+23 };

    return 0;
}
