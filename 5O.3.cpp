#include <iostream>

void meaningfulUint_t();
void meaningfulBitset();
void RGBA();

int main()
{
    constexpr std::uint8_t mask0{ 0b0000'0001 };
    constexpr std::uint8_t mask1{ 0b0000'0010 };
    constexpr std::uint8_t mask2{ 0b0000'0100 };
    constexpr std::uint8_t mask3{ 0b0000'1000 };
    constexpr std::uint8_t mask4{ 0b0001'0000 };
    constexpr std::uint8_t mask5{ 0b0010'0000 };
    constexpr std::uint8_t mask6{ 0b0100'0000 };
    constexpr std::uint8_t mask7{ 0b1000'0000 };

    std::uint8_t flags{ 0b1011'0010 };
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags) << '\n';

    // testing
    std::cout << "bit 1 is " << (static_cast<std::bitset<8>>(flags).test(1) ? "on" : "off")
        << ", bit 6 is " << (static_cast<std::bitset<8>>(flags).test(6) ? "on" : "off") << '\n'; 
    std::cout << "bit 1 is " << ((static_cast<std::bitset<8>>(flags & mask1)).any() ? "on" : "off")
        << ", bit 6 is " << ((static_cast<std::bitset<8>>(flags & mask6)).any() ? "on" : "off") << '\n';
    std::cout << "bit 1 is " << ((flags & mask1) ? "on" : "off")
        << ", bit 6 is " << ((flags & mask6) ? "on" : "off" ) << '\n';

    // setting
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags).set(0).set(2) << '\n';
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags | mask0 | mask2) << '\n';

    // resetting
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags).reset(1).reset(5) << '\n';
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags & ~(mask1 | mask5)) << '\n';

    // flipping
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags).flip(0).flip(1).flip(2).flip(3) << '\n';
    std::cout << "flags : " << static_cast<std::bitset<8>>(flags ^ mask0 ^ mask1 ^ mask2 ^ mask3) << '\n';

    meaningfulUint_t();
    meaningfulBitset();
    RGBA();

    return 0;
}

void meaningfulUint_t()
{
    std::cout << '\n';
    constexpr std::uint8_t isHungry     { 1 << 0 };
    constexpr std::uint8_t isSad        { 1 << 1 };
    constexpr std::uint8_t isMad        { 1 << 2 };
    constexpr std::uint8_t isHappy      { 1 << 3 };
    constexpr std::uint8_t isLaughing   { 1 << 4 };
    constexpr std::uint8_t isAsleep     { 1 << 5 };
    constexpr std::uint8_t isDead       { 1 << 6 };
    constexpr std::uint8_t isCrying     { 1 << 7 };

    std::uint8_t me{};
    me |= (isHappy | isLaughing);
    me &= ~isLaughing;

    std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << ' '
        << ((me & isHappy) == isHappy) << '\n';
    std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing)<< ' '
        << ((me & isLaughing) == isLaughing) << '\n';
}

void meaningfulBitset()
{
    std::cout << '\n';
    constexpr std::bitset<8> isHungry     { 1 << 0 };
    constexpr std::bitset<8> isSad        { 1 << 1 };
    constexpr std::bitset<8> isMad        { 1 << 2 };
    constexpr std::bitset<8> isHappy      { 1 << 3 };
    constexpr std::bitset<8> isLaughing   { 1 << 4 };
    constexpr std::bitset<8> isAsleep     { 1 << 5 };
    constexpr std::bitset<8> isDead       { 1 << 6 };
    constexpr std::bitset<8> isCrying     { 1 << 7 };

    std::bitset<8> me{};
    me |= (isHappy | isLaughing);
    me &= ~isLaughing;
    
    std::cout << "I am happy? " << (me & isHappy).any()
        << ' ' << ((me & isHappy) == isHappy) << '\n';
    std::cout << "I am laughing? " << (me & isLaughing).any()
        << ' ' << ((me & isLaughing) == isLaughing) << '\n';
}

void RGBA()
{
    constexpr std::uint32_t redBits{ 0xff00'0000 };
    constexpr std::uint32_t greenBits{ 0x00ff'0000 };
    constexpr std::uint32_t blueBits{ 0x0000'ff00 };
    constexpr std::uint32_t alphaBits{ 0x0000'00ff };

    std::cout << "Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): ";
    std::uint32_t pixel{};
    std::cin >> std::hex >> pixel;

    std::uint8_t red{ static_cast<std::uint8_t>((pixel & redBits) >> 24) };
    std::uint8_t green{ static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
    std::uint8_t blue{ static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
    std::uint8_t alpha{ static_cast<std::uint8_t>(pixel & alphaBits) };

    std::cout << "Your color contains:\n";
    std::cout << std::hex;
    std::cout << static_cast<int>(red) << " red\n";
    std::cout << static_cast<int>(green) << " green\n";
    std::cout << static_cast<int>(blue) << " blue\n";
    std::cout << static_cast<int>(alpha) << " alpha\n";
}
