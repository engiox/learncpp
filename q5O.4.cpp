#include <iostream>
#include <cstdint>

std::uint8_t gtVal(std::uint8_t val, std::uint8_t pow);

int main()
{
    std::cout << "Enter a number between 0 and 255: ";
    std::uint8_t val{};
    std::cin >> val;

    
    return 0;
}

std::uint8_t gtVal(std::uint8_t val, std::uint8_t pow)
{
    if (val >= pow) {
        std::cout << '1';
        return val - pow;
    }
    return val;
}
