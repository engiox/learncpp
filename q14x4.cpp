#include <iostream>
#include <iomanip>
#include <ostream>
#include <cassert>
#include <cmath>

class FixedPoint2
{
    int16_t m_nonFrac{0};
    int8_t m_frac{0};

public:
    FixedPoint2(int16_t nfrac, int8_t frac) : m_nonFrac{ nfrac }, m_frac{ frac }
    {
        assert( m_frac < 100 && m_frac > -100 && "Fractional part out of range!\n" );

        if (m_nonFrac < 0 && m_frac > 0) m_frac *= -1;
        if (m_nonFrac > 0 && m_frac < 0) m_nonFrac *= -1;
    }

    FixedPoint2(double dval)
    {
        m_nonFrac = static_cast<int>(trunc(dval));
        m_frac = static_cast<int>(round((dval - m_nonFrac)*100));
        if (dval < 0)
            m_frac = -m_frac;
        if (m_frac == 100) {
            ++m_nonFrac;
            m_frac = 0;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const FixedPoint2& fp2)
    {
        out << (fp2.m_nonFrac == 0 && fp2.m_frac < 0 ? "-" : "") << fp2.m_nonFrac;
        if (fp2.m_frac) {
            out << '.' << abs(fp2.m_frac / 10);
            if (fp2.m_frac % 10) {
                out << abs(fp2.m_frac % 10);
            }
//            out << '.' << std::setfill('0') << std::setw(2)
//            << (fp2.m_frac > 0 ? fp2.m_frac : -fp2.m_frac);
        }
        return out;
    }

    operator double() const
    {
        return static_cast<double>(m_frac)/100 + m_nonFrac;
    }

    friend bool operator==(FixedPoint2& v1, FixedPoint2& v2)
    {
        return ((v1.m_nonFrac == v2.m_nonFrac) && (v1.m_frac == v2.m_frac));
    }

    friend std::istream& operator>>(std::istream& in, FixedPoint2& fp2)
    {
        double dval{};
        in >> dval;
        fp2 = FixedPoint2(dval);
        return in;
    }

    FixedPoint2 operator-() const
    {
        return {static_cast<int16_t>(-m_nonFrac), static_cast<int8_t>(-m_frac)};
    }

    friend FixedPoint2 operator+(const FixedPoint2& fp1, const FixedPoint2& fp2)
    {
        int base{fp1.m_nonFrac + fp2.m_nonFrac};
        int frac{fp1.m_frac + fp2.m_frac};
        
        while (frac >= 100) {
            frac -= 100;
            ++base;
        }
        while (frac <= -100) {
            frac += 100;
            --base;
        }

        return FixedPoint2(base, static_cast<char>(frac));
    }
};

void p1()
{
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';

	FixedPoint2 b{ -2, 8 };
	std::cout << b << '\n';

	FixedPoint2 c{ 2, -8 };
	std::cout << c << '\n';

	FixedPoint2 d{ -2, -8 };
	std::cout << d << '\n';

	FixedPoint2 e{ 0, -5 };
	std::cout << e << '\n';

	std::cout << static_cast<double>(e) << '\n';
}

void p2()
{
	// Handle cases where the argument is representable directly
	FixedPoint2 a{ 0.01 };
	std::cout << a << '\n';

	FixedPoint2 b{ -0.01 };
	std::cout << b << '\n';

	// Handle cases where the argument has some rounding error
	FixedPoint2 c{ 5.01 }; // stored as 5.0099999... so we'll need to round this
	std::cout << c << '\n';

	FixedPoint2 d{ -5.01 }; // stored as -5.0099999... so we'll need to round this
	std::cout << d << '\n';

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 e{ 106.9978 }; // should be stored with base 107 and decimal 0
	std::cout << e << '\n';

	FixedPoint2 f{ 1.9 }; // make sure we handle single digit decimal
	std::cout << f << '\n';
}

void testAddition()
{
	// h/t to reader Sharjeel Safdar for this function
	std::cout << std::boolalpha;
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 1.98 }) << '\n'; // both positive, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 2.25 }) << '\n'; // both positive, with decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -1.98 }) << '\n'; // both negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -2.25 }) << '\n'; // both negative, with decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.23 } == FixedPoint2{ -0.48 }) << '\n'; // second negative, no decimal overflow
	std::cout << (FixedPoint2{ 0.75 } + FixedPoint2{ -1.50 } == FixedPoint2{ -0.75 }) << '\n'; // second negative, possible decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.23 } == FixedPoint2{ 0.48 }) << '\n'; // first negative, no decimal overflow
	std::cout << (FixedPoint2{ -0.75 } + FixedPoint2{ 1.50 } == FixedPoint2{ 0.75 }) << '\n'; // first negative, possible decimal overflow
}

int main()
{
    p1();
    p2();
    testAddition();

	FixedPoint2 a{ -0.48 };
	std::cout << a << '\n';

	std::cout << -a << '\n';

	std::cout << "Enter a number: "; // enter 5.678
	std::cin >> a;

	std::cout << "You entered: " << a << '\n';

	return 0;
}
