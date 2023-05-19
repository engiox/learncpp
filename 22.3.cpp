#include <iostream>
#include <string>

int main()
{
    std::string strini{};
    std::cout << (strini.empty() ? "true" : "false" ) << '\n';

    std::string s { "0123456789abcde" };
    std::cout << "Length: " << s.length() << '\n';
    std::cout << "Capacity: " << s.capacity() << '\n';

    s += "f";
    std::cout << "Length: " << s.length() << '\n';
    std::cout << "Capacity: " << s.capacity() << '\n';
 
    return 0;
}
