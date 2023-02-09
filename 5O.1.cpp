#include <iostream>
#include <bitset>

int main()
{
    std::bitset<8> mybitset {};
    std::bitset<7> mybitseven {};
    std::bitset<12> mybit12 {};
    std::bitset<16> mybit16 {};

    std::cout << "sizeof(bitset<8>) = " << sizeof(mybitset) << '\n';
    std::cout << "sizeof(bitset<7>) = " << sizeof(mybitseven) << '\n';
    std::cout << "sizeof(bitset<12>) = " << sizeof(mybit12) << '\n';
    std::cout << "sizeof(bitset<16>) = " << sizeof(mybit16) << '\n';

    return 0;
}
