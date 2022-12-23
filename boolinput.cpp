#include <iostream>

bool returnBool()
{
    return 6;
}

int main()
{
    bool b{ true };
    std::cout << "Initial value: " << b << '\n';
    std::cout << "Enter a boolean value: ";
    std::cin >> b;
    std::cout << "You entered: " << b << '\n';

    std::cout << "Returning bool value from function: " << returnBool() << '\n';

    return 0;
}
