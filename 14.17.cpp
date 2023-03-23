#include <iostream>
#include <ostream>

template<typename T>
const T& max(const T& v1, const T& v2)
{
    return (v1 > v2) ? v1 : v2;
}

template<typename T>
T average(const T* myArray, int numVals)
{
    T sum{0};
    for (int i{0}; i < numVals; ++i) {
        sum += myArray[i];
    }

    return sum/=numVals;
}

class Cents
{
    int m_cents{0};

public:
    Cents(int cents) : m_cents{ cents } {}
    bool operator>(const Cents& arg) const
    {
        return (m_cents > arg.m_cents);
    }
    bool operator<(const Cents& arg)
    {
        return arg > *this;
    }
    Cents& operator+=(const Cents& arg)
    {
        m_cents += arg.m_cents;
        return *this;
    }

    Cents& operator/=(int den)
    {
        m_cents /= den;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Cents& cent)
    {
        out << cent.m_cents;
        return out;
    }
};

void part1()
{
    Cents nickel{ 5 };
    Cents dime{ 10 };

    Cents bigger = max(nickel, dime);
    std::cout << bigger << " is bigger\n";
}

void part2()
{
    int intArray[]{ 5, 3, 2, 1, 4 };
    std::cout << average(intArray, 5) << '\n';

    double doubleArray[]{ 3.12, 3.45, 9.23, 6.34 };
    std::cout << average(doubleArray, 4) << '\n';
}

void part3()
{
    Cents centArray[]{ 5, 10, 15, 14 };
    std::cout << average(centArray, 4) << '\n';
}

int main()
{
    part1();
    part2();
    part3();

    return 0;
}
