#include "Digit.h"

Digit::Digit(int digit) : m_digit{digit}
{
}

Digit& Digit::operator++()
{
    if (m_digit == 9)
        m_digit = 0;
    else
        ++m_digit;
    return *this;
}

Digit& Digit::operator--()
{
    if (m_digit == 0)
        m_digit = 9;
    else
        --m_digit;
    return *this;
}

Digit Digit::operator++(int)
{
    Digit tmp{*this};
    ++*this;
    return tmp;
}

Digit Digit::operator--(int)
{
    Digit tmp{*this};
    --*this;
    return tmp;
}

std::ostream &operator<<(std::ostream &out, const Digit &digit)
{
    out << digit.m_digit;
    return out;
}
