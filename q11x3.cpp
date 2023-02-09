#include <iostream>

void swapInt(int &a, int &b)
{
    int temp{ a };
    a = b;
    b = temp;
}

int main()
{
    int a{ 6 }, b{ 3 };

    swapInt(a, b);

    std::cout << a << ' ' << b << '\n';

    return 0;
}
