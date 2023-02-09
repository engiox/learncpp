#include <iostream>

int main()
{
    std::int8_t myint{65};
    std::cout << myint << '\n';

    std::cout << "Enter a number between 0 and 255: ";
    std::int8_t myint2{};
    std::cin >> myint2;

    std::cout << "You entered: " << static_cast<int>(myint2) << '\n';

    return 0;
}
