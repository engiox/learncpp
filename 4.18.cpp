#include <iostream>

void printSV(std::string_view);

int main()
{
    std::string_view s{"Hello, awkwardly wonderful world!\n"};
    printSV(s);
    std::cout << "sizeof(s): " << sizeof(s) << '\n';

    std::cout << "Enter your name: ";
    std::string buffer{};
    std::cin >> buffer;
    std::string_view s2{buffer};
    std::cout << s2 << ", new string_view has been created\n";

    using namespace std;
    std::cout << "foo\n";
    std::cout << "goo\n"s;
    std::cout << "moo\n"sv;

    return 0;
}

void printSV(std::string_view str)
{
    std::cout << str << '\n';
}
