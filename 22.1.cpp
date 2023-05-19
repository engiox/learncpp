#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    std::string str;

    std::cout << std::setw(16) << "capacity() : " << str.capacity() << '\n';
    std::cout << std::setw(16) << "empty() : " << str.empty() << '\n';
    std::cout << std::setw(16) << "max_size() : " << str.max_size() << '\n';

    std::cout << '\n';

    return 0;
}
