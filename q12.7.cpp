#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <string_view>
#include <functional>

void q1();
void q2();

struct Student {
    std::string stuName{};
    int stuPoint{};
};

struct Season {
    std::string_view ssnName{};
    double avgTemp{};
};

int main()
{
    q1();
    q2();
    return 0;
}

void q1()
{
    std::array<Student, 8> arr{{
        { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 },       // Magna Cum Laude
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 }
    }};

    const auto MCL{ std::max_element(arr.begin(), arr.end(),
            [](Student a, Student b) { return (a.stuPoint < b.stuPoint); }) };

    std::cout << MCL->stuName << " is the best student with "
              << (*MCL).stuPoint << " points\n";
}

void q2()
{
    std::array<Season, 4> seasons{{
            { "Spring", 285.0 },
            { "Summer", 296.0 },
            { "Fall", 288.0 },
            { "Winter", 263.0 }
    }};

    std::sort(seasons.begin(), seasons.end(),
            [](Season a, Season b) { return (a.avgTemp < b.avgTemp); });

    for (const auto &season : seasons) {
        std::cout << season.ssnName << " : " << season.avgTemp << '\n';
    }
}
