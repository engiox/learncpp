#include <ios>
#include <iostream>
#include <typeinfo>

int main()
{
    int i{ 2 };
    double d{ 3.5 };
    std::cout << typeid(i + d).name() << ' ' << i + d << '\n';

    short a{ 4 }, b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n';

    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n';

    std::cout << std::boolalpha << (-3 < 5u) << '\n';

    return 0;
}
