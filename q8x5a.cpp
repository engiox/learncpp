#include <iostream>

template <typename T>
T add(T v1, T v2)
{
    return v1 + v2;
}

int main()
{
    std::cout << add(2, 3) << '\n';
    std::cout << add(1.2, 3.4) << '\n';

    return 0;
}
