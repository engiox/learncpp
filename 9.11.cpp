#include <iostream>
#include <string>

const std::string& getProgramName() // returns a const reference
{
    static const std::string s_programName { "Calculator\n" }; // has static duration, destroyed at end of program

    return s_programName;
}

const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int& max(int& a, int& b)
{
    return (a > b) ? a : b;
}

int main()
{
    std::cout << "This program is named " << getProgramName();

    std::string hello{ "Hello" };
    std::string world{ "World" };

    std::cout << firstAlphabetical(hello, world) << '\n';

    int a{ 5 }, b{ 6 };
    max(a, b) = 7;
    std::cout << a << b << '\n';

    return 0;
}
