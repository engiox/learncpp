#include <iostream>
#include <vector>
#include <cmath>
#include "Random.h"

int main()
{
    int iStart{}, iNum{};
    std::cout << "Start where? ";
    std::cin >> iStart;
    std::cout << "How many? ";
    std::cin >> iNum;

    std::vector<int> arr{ [iStart, iNum](){
        std::vector<int> v{};
        for (int i{iStart}; i <= iStart + iNum; ++i)
            v.push_back(i*i);
        return v;
    }() };

//    for (auto e:arr) std::cout << e << ' ';
//    std::cout << '\n';

    int iRan{Random::get(2, 4)};

    std::cout << "I generated " << iNum << " numbers."
        "Do you know what each number is after multiplying it by "
        << iRan << "?\n";

    for (auto &e:arr) e *= iRan;

//    for (auto e:arr) std::cout << e << ' ';
//    std::cout << '\n';

//    for (int i{0}; i < iNum; ++i) {
    for (;iNum;) {
        std::cout << "> ";
        int iAns{};
        std::cin >> iAns;
        auto found{ std::find(arr.begin(), arr.end(), iAns) };
        if (found == arr.end()) {
            std::cout << iAns << " is wrong!\n";
            break;
        }
        arr.erase(found);
        std::cout << "Nice! ";
        if (--iNum) std::cout << iNum << " number(s) left.\n";
        else std::cout << "You found all numbers, good job!\n";
    }
    return 0;
}
