#include <iostream>
#include <bitset>

std::bitset<4> rotl(std::bitset<4> bits);

int main()
{
    std::bitset<4> bits1{ 0b0001 };
    std::cout << rotl(bits1) << '\n';

    std::bitset<4> bits2{ 0b1001 };
    std::cout << rotl(bits2) << '\n';

    return 0;
}

std::bitset<4> rotl(std::bitset<4> bits)
{
    if (bits.test(3))
        return (bits << 1) | std::bitset<4> { 0b0001 };
    return bits << 1;
}
