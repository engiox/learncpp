#include <iostream>

int main()
{
    char a {'a'}, b {'b'};
    std::cout << (a, b) << '\n';

    for (int x{0}, y{9}; x < 10; ++x, --y) {
        std::cout << x << ' ' << y << '\n';
    }

    return 0;
}
