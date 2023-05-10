#include <iostream>

class Fraction
{
    int m_numerator;
    int m_denominator;
public:
    Fraction(int num, int den) : m_numerator{ num }, m_denominator{ den } {}
    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac)
    {
        os << frac.m_numerator << '/' << frac.m_denominator;
        return os;
    }
};

void fun(const int& lref)
{
    std::cout << "l-value reference to const: " << lref << '\n';
}

void fun(int&& rref)
{
    std::cout << "r-value reference: " << rref << '\n';
}

int main()
{
    Fraction&& rref{ Fraction{ 3, 5 } };
    std::cout << rref << '\n';
    const Fraction& lref{ Fraction{ 1, 3 } };
    std::cout << lref << '\n';
    {
        rref = Fraction{ 3, 6 };
    }
    std::cout << rref << '\n';

    int x{ 5 };
    fun(x);
    fun(5);

    return 0;
}
