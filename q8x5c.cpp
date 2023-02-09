#include <iostream>

template <typename T, typename U>
auto sub(T x, U y)
{
    return x - y;
}

auto mod(auto x, auto y)
{
    return x % y;
}

int main()
{
    std::cout << sub(3, 2) << '\n';
    std::cout << sub(3.5, 2) << '\n';
    std::cout << sub(4, 1.5) << '\n';

    std::cout << mod(10, 3) << '\n';

    return 0;
}
