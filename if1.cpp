#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x)
        std::cout << "Entered value: " << x << '\n';

    return 0;
}
