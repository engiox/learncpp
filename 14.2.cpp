#include <iostream>
#include <numeric>

class Fraction
{
    int m_numerator{};
    int m_denominator{};
public:
    Fraction(int num = 0, int den = 1) : m_numerator{num}, m_denominator{den} {}
    void print() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }
    Fraction &reduce()
    {
        int gcd{std::gcd(m_numerator, m_denominator)};
        if (gcd) {
            m_numerator /= gcd;
            m_denominator /= gcd;
        }
        return *this;
    }

//    friend Fraction operator*(const Fraction v1, const Fraction v2);
    friend Fraction operator*(const Fraction &v1, const Fraction &v2);
    friend Fraction operator*(const Fraction &vf, int vi);
    friend Fraction operator*(int vi, const Fraction &vf) { return vf * vi; }
};

Fraction operator*(const Fraction &v1, const Fraction &v2)
{
    return Fraction{v1.m_numerator * v2.m_numerator, v1.m_denominator * v2.m_denominator};
}

Fraction operator*(const Fraction &vf, int vi)
{
    return Fraction{vf.m_numerator * vi, vf.m_denominator};
}

int main()
{
    Fraction f1{2, 5};
    f1.print(); std::cout << "reduces to ";
    f1.reduce().print();

    Fraction f2{3, 8};
    f2.print(); std::cout << "reduces to ";
    f2.reduce().print();

    Fraction f3{ f1 * f2 };
    f3.print(); std::cout << "reduces to ";
    f3.reduce().print();

    Fraction f4{ f1 * 2 };
    f4.print(); std::cout << "reduces to ";
    f4.reduce().print();

    Fraction f5{ 2 * f2 };
    f5.print(); std::cout << "reduces to ";
    f5.reduce().print();

    Fraction f6{ Fraction{1, 2} * Fraction{2, 3} * Fraction{3, 4} };
    f6.print(); std::cout << "reduces to ";
    f6.reduce().print();
    f6.print();

    return 0;
}
