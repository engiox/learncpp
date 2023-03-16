#include <ios>
#include <iostream>
#include <limits>
#include <numeric>
#include "Fraction.h"

Fraction::Fraction(int num, int den) : m_numerator{num}, m_denominator{den}
{
    reduce();
}

void Fraction::print()
{
    std::cout << m_numerator << '/' << m_denominator << '\n';
}

Fraction operator*(const Fraction &f1, const Fraction &f2)
{
    return Fraction{f1.m_numerator * f2.m_numerator, f1.m_denominator * f2.m_denominator};
}

Fraction operator*(const Fraction &f1, int inum)
{
    return Fraction{f1.m_numerator * inum, f1.m_denominator};
}

Fraction operator*(int inum, const Fraction &f1) { return f1 * inum; }

Fraction &Fraction::reduce()
{
    int gcd{ std::gcd(m_numerator, m_denominator) };
    if (gcd) {
        m_numerator /= gcd;
        m_denominator /= gcd;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Fraction &fr)
{
    out << fr.m_numerator << '/' << fr.m_denominator ;
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &fr)
{
    in >> fr.m_numerator;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '/');
    in >> fr.m_denominator;

    return in;
}
