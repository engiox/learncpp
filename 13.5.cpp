#include <iostream>
#include <cassert>

class Fraction
{
    private:
        int m_numerator{};
        int m_denominator{};

    public:
        Fraction(int num = 0, int den = 1) {
            assert(den != 0 && "Divided by zero in class Fraction\n");
            m_numerator = num; m_denominator = den;
        }
//        Fraction() { m_numerator = 0; m_denominator = 1; }
//        Fraction(int num, int den) {
//            assert(den != 0 && "Divided by Zero in Fraction\n");
//            m_numerator = num; m_denominator = den;
//        }
        int getNumerator() { return m_numerator; }
        int getDemoninator() { return m_denominator; }
        double getValue() { return static_cast<double>(m_numerator) / m_denominator; }
};

class Something
{
    int num{};
    double ratio{};
    public:
        Something(int n=0, double d=1.2) { num = n; ratio = d; }
};

class Date
{
    int m_year{1900};
    int m_month{1};
    int m_day{1};

    public:
//        Date() {}
        Date() = default;
        Date(int y, int m, int d) { m_year = y; m_month = m; m_day = d; }
        void print() { std::cout << m_year << '/' << m_month << '/' << m_day << '\n'; }
};

int main()
{
    Fraction frac[6];
    Fraction zero;
    Fraction zeroe{};
    Fraction siz{6};
    Fraction twothird{2, 3};
    Fraction fivethird(5, 3);
//    for (int i{0}; i < 6; ++i) {
//        std::cout << frac[i].getNumerator() << '/' << frac[i].getDemoninator() << '\n';
//    }

    Something s1{1, 2.4};
    Something s2{2};
    Something s3{};
//    Something s4{3.6};

    Date today{ 2020, 1, 19 };
    today.print();
    Date someday{};
    someday.print();

    return 0;
}
