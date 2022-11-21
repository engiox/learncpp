#include <iostream>

int main()
{
    bool b{ true };
    std::cout << "Initial value: " << b << '\n';
    std::cout << "Enter a boolean value: ";
    std::cin >> b;
    std::cout << "You entered: " << b << '\n';

    return 0;
}
