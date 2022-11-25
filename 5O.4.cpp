#include <iostream>
#include <cstdint>
#include <bitset>
#include <iomanip>

int main()
{
    for (uint8_t i = 0b0000'0000; i <= 0b1111'1111; ++i) {
        std::cout << static_cast<std::bitset<8>>(i) << " : "
            << static_cast<int>(i) << " : " << static_cast<unsigned>(i)
            << ((i % 4 == 0) ? '\n' : '\t');
    }
    return 0;
}
