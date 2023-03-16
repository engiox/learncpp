#include "Digit.h"

int main()
{
    Digit digit1(8);

    std::cout << digit1;
    std::cout << ++digit1;
    std::cout << ++digit1;
    std::cout << --digit1;
    std::cout << --digit1 << '\n';

    Digit digit2(5);

    std::cout << digit2;
    std::cout << ++digit2; // calls digit2::operator++();
    std::cout << digit2++; // calls digit2::operator++(int);
    std::cout << digit2;
    std::cout << --digit2; // calls digit2::operator--();
    std::cout << digit2--; // calls digit2::operator--(int);
    std::cout << digit2 << '\n';

    return 0;
}
