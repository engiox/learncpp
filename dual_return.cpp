#include <iostream>

int main()
{
    char *a, b;
    std::cout << "char *a, b : sizeof(a) = " << sizeof(a) <<
        ", sizeof(b) = " << sizeof(b) << '\n';

    std::cout << "Enter two values for x and y : ";
    int x{}, y{};
    std::cin >> x >> y;
    std::cout << ((x > y) ? x : y) << '\n';

    return static_cast<void>(std::cout << "Testing\n"), x;
}
