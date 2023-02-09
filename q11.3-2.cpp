#include <ios>
#include <iostream>
#include <iterator>
#include <limits>

int getNumber()
{
    int ans {};
    while (true) {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> ans;

        if (ans >= 1 && ans <= 9) return ans;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int main()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };

    int val { getNumber() };

    for (size_t ind{ 0 }; ind < std::size(array); ++ind) {
        std::cout << array[ind] << ' ';
    }
    std::cout << '\n';

    for (size_t ind{ 0 }; ind < std::size(array); ++ind) {
        if (val == array[ind]) {
            std::cout << "The number " << val << " has index " << ind << '\n';
        }
    }

    return 0;
}
