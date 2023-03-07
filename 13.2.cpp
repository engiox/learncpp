#include <iostream>

struct DateStruct
{
    int year{};
    int month{};
    int day{};
};

void print(const DateStruct &date)
{
    std::cout << date.year << '/' << date.month << '/' << date.day << '\n';
}

class DateClass
{
    public:
    int m_year{};
    int m_month{};
    int m_day{};

    void print() { std::cout << m_year << '/' << m_month << '/' << m_day << '\n'; }
};

int main()
{
    DateStruct yesterda{ 2022, 3, 6 };
    DateClass today{ 2022, 3, 7 };

    yesterda.day = 16;
    print(yesterda);
    today.m_day = 17;
    today.print();

    return 0;
}
