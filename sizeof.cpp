#include <iostream>
#include <string>
#include <string_view>

struct dummyStruct
{
};

int main()
{
    std::cout << "bool:\t\t" << sizeof(bool) << " bytes\n";
    std::cout << "char:\t\t" << sizeof(char) << " bytes\n";
    std::cout << "wchar_t:\t" << sizeof(wchar_t) << " bytes\n";
    std::cout << "char16_t:\t" << sizeof(char16_t) << " bytes\n";
    std::cout << "char32_t:\t" << sizeof(char32_t) << " bytes\n";
    std::cout << "short:\t\t" << sizeof(short) << " bytes\n";
    std::cout << "int:\t\t" << sizeof(int) << " bytes\n";
    std::cout << "666 :\t\t" << sizeof(666) << " bytes\n";
    std::cout << "long:\t\t" << sizeof(long) << " bytes\n";
    std::cout << "666l:\t\t" << sizeof(666l) << " bytes\n";
    std::cout << "long long:\t" << sizeof(long long) << " bytes\n";
    std::cout << "float:\t\t" << sizeof(float) << " bytes\n";
    std::cout << "3.14f:\t\t" << sizeof(3.14f) << " bytes\n";
    std::cout << "double:\t\t" << sizeof(double) << " bytes\n";
    std::cout << "3.1415:\t\t" << sizeof(3.1415) << " bytes\n";
    std::cout << "long double:\t" << sizeof(long double) << " bytes\n";
    std::cout << "pointer:\t" << sizeof(int *) << " bytes\n";
    std::cout << "string:\t\t" << sizeof(std::string) << " bytes\n";
    std::cout << "string_view:\t" << sizeof(std::string_view) << " bytes\n";
    std::cout << "dummy struct:\t" << sizeof(dummyStruct) << " bytes\n";

    std::cout << "\nSize of int array? ";
    int szint{};
    std::cin >> szint;
    int* arrInt{ new int[szint] };
    std::cout << "sizeof *arrInt[] : " << sizeof(arrInt) << '\n';

    return 0;
}
