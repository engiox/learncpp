#include <cstdint>

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
};
