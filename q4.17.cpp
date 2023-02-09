#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter your age: ";
    unsigned age{};
    std::cin >> age;

    std::cout << "Your age + length of name is :" << age + name.length() << '\n';

    return 0;
}
