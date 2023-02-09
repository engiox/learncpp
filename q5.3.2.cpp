#include <iostream>

bool isEven(int);

bool isEven(int val)
{
    return ( val % 2 == 0 );
}

int main()
{
    std::cout << "Enter an integer: ";
    int val{};
    std::cin >> val;

    if (isEven(val)) std::cout << val << " is Even\n";
    else std::cout << val << " is Odd\n";

    return 0;
}
