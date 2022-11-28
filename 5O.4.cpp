#include <iostream>
#include <cstdint>
#include <bitset>
#include <iomanip>

int main()
{
    for (uint8_t i = 0b0000'0000; ; ++i) {
        std::cout << static_cast<std::bitset<8>>(i) << " : " << std::setw(3)
            << static_cast<int>(i) << " : " << std::setw(3) << static_cast<unsigned>(i)
            << (((i+1) % 4 == 0) ? '\n' : '\t');
        if (i == 0b1111'1111) break;
    }
    return 0;
}
