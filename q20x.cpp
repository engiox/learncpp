#include <iostream>
#include <exception>
#include <stdexcept>

class Fraction
{
    int m_numerator{};
    int m_denominator{};
public:
    Fraction(int num = 0, int den = 1) : m_numerator{num}, m_denominator{den}
    {
        if (!den)
            throw std::runtime_error("Invalid denominator");
    }
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fr);
};


std::ostream& operator<<(std::ostream& os, const Fraction& fr)
{
    os << fr.m_numerator << '/' << fr.m_denominator;
    return os;
}

int main()
{
    std::cout << "Enter the numerator: ";
    int num{};
    std::cin >> num;
    std::cout << "Enter the denominator: ";
    int den{};
    std::cin >> den;

    try {
        Fraction frac(num, den);
        std::cout << "Fraction: " << frac << '\n';
    }
    catch (const std::exception& expt) {
        std::cerr << expt.what() << '\n';
    }

    return 0;
}
