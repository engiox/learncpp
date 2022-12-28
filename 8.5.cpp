#include <iostream>
#include <iomanip>

int main()
{
    for (int i{0}; i < 256; ++i) {
        std::cout << std::setw(4) << i << " : "
            << static_cast<unsigned char>(i) << '\n';
    }
    return 0;
}
