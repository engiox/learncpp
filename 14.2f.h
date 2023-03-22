#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <iostream>

class Fraction
{
    int m_numerator{0};
    int m_denominator{1};
public:
    Fraction(int num = 0, int den = 1); // : m_numerator{num}, m_denominator{den} {}
    Fraction(const Fraction& fr);
    void setNumerator(int num);
    int getNumerator();
    void print();
    Fraction &reduce();
    Fraction& operator=(const Fraction& fr);
    friend Fraction operator*(const Fraction &f1, const Fraction &f2);
    friend Fraction operator*(const Fraction &f1, int inum);
    friend Fraction operator*(int inum, const Fraction &f1); // { return f1 * inum; }
    friend std::ostream &operator<<(std::ostream &out, const Fraction &fr);
    friend std::istream &operator>>(std::istream &in, Fraction &fr);
    friend bool operator==(const Fraction &f1, const Fraction &f2);
    friend bool operator!=(const Fraction &f1, const Fraction &f2);
    friend bool operator<(const Fraction &f1, const Fraction &f2);
    friend bool operator>(const Fraction &f1, const Fraction &f2);
    friend bool operator<=(const Fraction &f1, const Fraction &f2);
    friend bool operator>=(const Fraction &f1, const Fraction &f2);
};

#endif
