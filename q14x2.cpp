#include <iostream>
#include <cstdint>
#include <ostream>

class Average
{
    std::int32_t sum{0};
    std::int8_t  num{0};
public:
    Average(){}
    Average& operator+=(int add)
    {
        sum += add;
        ++num;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const Average& avg)
    {
        ostr << static_cast<double>(avg.sum) / avg.num;
        return ostr;
    }
};

int main()
{
	Average avg{};

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}
