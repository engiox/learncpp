#include <ios>
#include <iostream>
#include <limits>
#include <numeric>
#include <cassert>
#include "Fraction.h"

Fraction::Fraction(int num, int den) : m_numerator{num}, m_denominator{den}
{
    assert(m_denominator != 0 && "Constructor: divided by zero!\n");
    reduce();
}

Fraction::Fraction(const Fraction& fr) : m_numerator{ fr.m_numerator }, m_denominator{ fr.m_denominator }
{
    std::cout << "Copy constructor called\n";
}

void Fraction::setNumerator(int num)
{
    m_numerator = num;
}

int Fraction::getNumerator()
{
    return m_numerator;
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

bool operator==(const Fraction &f1, const Fraction &f2)
{
    return (f1.m_numerator == f2.m_numerator && f1.m_denominator == f2.m_denominator);
}

bool operator<(const Fraction &f1, const Fraction &f2)
{
    return (f1.m_numerator * f2.m_denominator < f2.m_numerator * f1.m_denominator);
}

bool operator!=(const Fraction &f1, const Fraction &f2)
{
    return !(f1 == f2);
}

bool operator>(const Fraction &f1, const Fraction &f2)
{
    return (f2 < f1);
}

bool operator<=(const Fraction &f1, const Fraction &f2)
{
    return !(f1 > f2);
}

bool operator>=(const Fraction &f1, const Fraction &f2)
{
    return !(f1 < f2);
}

