#include <iostream>
#include <random>
#include <array>
#include <vector>

int main()
{
    std::random_device rd;
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };

    std::uniform_int_distribution die6{1, 6};
    std::mt19937 mt{ss};

    for (int i{0}; i < 20; ++i) {
        std::cout << die6(mt) << ' ';
    }

    return 0;
}
