#include <iostream>
#include <string>

int main()
{
    std::string sString;

    sString += "one";
    sString.append(std::string(" two"));
    sString.push_back('t');

    std::cout << sString << '\n';
}
