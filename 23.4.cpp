#include <iostream>
#include <sstream>

int main()
{
    std::stringstream os;
    os << "Hello ";

    os.str(std::string());
    os.clear();

    os << "World!\n";

    std::cout << os.str();

    return 0;
}
