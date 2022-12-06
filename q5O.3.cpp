#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    constexpr std::uint8_t option_viewed{ 0x01 };
    constexpr std::uint8_t option_edited{ 0x02 };
    constexpr std::uint8_t option_favorited{ 0x04 };
    constexpr std::uint8_t option_shared{ 0x08 };
    constexpr std::uint8_t option_deleted{ 0x10 };

    std::uint8_t myArticleFlags{ option_favorited };

    myArticleFlags |= option_viewed;                            // a)

    std::cout << std::bitset<8>{ myArticleFlags } << '\n';

    if (myArticleFlags & option_deleted)                        // b)
        std::cout << "Your article has been deleted!\n";

    myArticleFlags &= ~option_favorited;                        // c)
    std::cout << std::bitset<8>{ myArticleFlags } << '\n';

    return 0;
}
