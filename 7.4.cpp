#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int num {};

    switch (std::cin >> num; num) {
        case 1:
            std::cout << "One\n";
            break;
        case 2:
            std::cout << "Two\n";
            break;
        case 3:
            std::cout << "Three\n";
            break;
        default:
            std::cout << "There are only three members!\n";
            break;
    }

    return 0;
}
