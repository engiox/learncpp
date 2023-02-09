#include <iostream>

int main()
{
    constexpr int temp { 5 };
    size_t daysPerWeek { temp };

    int numberOfLessonsPerDay[daysPerWeek] {};

    std::cout << sizeof(numberOfLessonsPerDay) << '\n';

    return 0;
}
