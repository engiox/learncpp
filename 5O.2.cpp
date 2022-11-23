#include <iostream>
#include <bitset>

int main()
{
    std::bitset<4> x {0b1100};

    std::cout << "x {0b1100} = " << x << ", and sizeof(x) = " << sizeof(x) << '\n';
    std::cout << "x >> 1 = " << (x >> 1) << '\n';
    std::cout << "x << 1 = " << (x << 1) << '\n';

    std::cout << std::bitset<4>{0b0100} << ' '
              << std::bitset<6>{0b0100} << ' '
              << std::bitset<8>{0b0100} << '\n';

    std::cout << ~std::bitset<4>{0b0100} << ' '
              << ~std::bitset<6>{0b0100} << ' '
              << ~std::bitset<8>{0b0100} << '\n';

    return 0;
}
