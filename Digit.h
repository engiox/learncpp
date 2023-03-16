#ifndef _DIGIT_H_
#define _DIGIT_H_

#include <iostream>

class Digit
{
    int m_digit{0};
public:
    Digit(int digit);

    Digit &operator++();
    Digit &operator--();

    Digit operator++(int);
    Digit operator--(int);

    friend std::ostream &operator<<(std::ostream &out, const Digit &digit);
};

#endif
