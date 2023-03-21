#include <iostream>
#include "Fraction.h"

Fraction makeNegative(Fraction f)
{
    f.setNumerator(-f.getNumerator());
    return f;
}

int main()
{
    Fraction fiveThirds(5, 3);
    std::cout << makeNegative(fiveThirds) << '\n';

    return 0;
}
