#include <iostream>

int getInteger()
{
    static bool s_isFirstCall{ true };

    if (s_isFirstCall) {
        std::cout << "Enter an integer: ";
        s_isFirstCall = false;
    }
    else {
        std::cout << "Enter another integer: ";
        s_isFirstCall = true;
    }

    int i{};
    std::cin >> i;
    return i;
}

int main()
{
    std::cout << "Addition\n";

    int a{ getInteger() };
    int b{ getInteger() };

    std::cout << a << " + " << b << " = " << (a + b) << '\n';

    std::cout << "Subtraction\n";

    int c{ getInteger() };
    int d{ getInteger() };

    std::cout << c << " - " << d << " = " << (c - d) << '\n';

    return 0;
}
