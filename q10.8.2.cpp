#include <iostream>

struct Fraction
{
    int numerator {};       // default : 0
    int denominator {};     // default : 1 (Avoid divided by ZERO)
};

Fraction getFraction()
{
    Fraction temp {};

    std::cout << "Enter a value for the numerator: ";
    std::cin >> temp.numerator;
    std::cout << "Enter a value for the denominator: ";
    std::cin >> temp.denominator;

    std::cout << '\n';      // Answer

    return temp;
}

Fraction multiplyFraction(const Fraction& frac1, const Fraction& frac2)
{
    Fraction result {};

    result.numerator = frac1.numerator * frac2.numerator;
    result.denominator = frac1.denominator * frac2.denominator;

    return result;
}

Fraction multiply(const Fraction& f1, const Fraction& f2)
{
    return {f1.numerator * f2.numerator, f1.denominator * f2.denominator};
}

void printFraction(const Fraction& frac)
{
    std::cout << frac.numerator << " / " << frac.denominator << '\n';
}

int main()
{
    Fraction val1 { getFraction() }, val2 { getFraction() };

    std::cout << "Your fractions multiplied together: ";
//    printFraction( multiplyFraction(val1, val2) );
    printFraction(multiply(val1, val2));

    return 0;
}
