#include <iostream>

int main()
{
    int o{077};
    std::cout << o << '\n';

    int x{0xff};
    std::cout << x << '\n';

    int b { 0b1111'0'1111'01 };
    std::cout << std::hex << b << '\n';

    b = 0b111'1011'1101;
    std::cout << std::hex << b << '\n';

    return 0;
}
