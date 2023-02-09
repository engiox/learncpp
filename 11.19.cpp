#include <array>
#include <functional>
#include <iostream>
#include <algorithm>
#include <algorithm>
#include <string_view>
#include <functional>

bool containsNut(std::string_view str)
{
    return (str.find("nut") != std::string_view::npos);
}

bool iGreater(int a, int b)
{
    return (a > b);
}

template <typename T, size_t num>
void printArray(const std::array<T, num> &arr)
{
    for (auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

void doubleNumber(int &i)
{
    i *= 2;
}

void halfNumber(int &i)
{
    i /= 2;
}

int main()
{
    // std::find
    {
        std::array arr{ 13, 90, 99, 5, 40, 80 };

        std::cout << "Enter a value to search for and replace with: ";
        int iSearch{}, iReplace{};
        std::cin >> iSearch >> iReplace;

        auto itFound{ std::find(arr.begin(), arr.end(), iSearch) };

        if ( itFound == arr.cend() ) {
            std::cout << "Could not find " << iSearch << '\n';
        } else {
            *itFound = iReplace;
        }

        for (auto i : arr) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
    // std::find_if
    {
        std::array<std::string_view, 4> arr{"apple", "banana", "walnut",
                                            "lemon"};

        auto found{std::find_if(arr.begin(), arr.end(), containsNut)};

        if (found == arr.end()) {
            std::cout << "No nuts\n";
        } else {
            std::cout << "Found " << *found << '\n';
        }
    }
    // std::count, std::count_if
    {
        std::array<std::string_view, 5> ar1{ "apple", "banana", "walnut", "lemon", "peanut" };

        using namespace std::literals;
        std::array arr{ "apple"sv, "banana"sv, "walnut"sv, "lemon"sv, "peanut"sv };

        auto iNuts{ std::count_if(arr.cbegin(), arr.cend(), containsNut) };

        std::cout << "Counted " << iNuts << " nut" << ( iNuts>0 ? "s." : "." ) << "\n";
    }
    // std::sort
    {
        std::array iArr{ 13, 90, 99, 5, 40, 80 };

        std::sort(iArr.begin(), iArr.end(), iGreater);
        printArray(iArr);

        std::sort(iArr.begin(), iArr.end(), std::less{});   // less{} is type. (std::function)
                                                            // Instantiating anonymous object
        printArray(iArr);
    }
    // std::for_each
    {
        std::array arr{ 1, 2, 3, 4 };

        std::for_each(arr.begin(), arr.end(), doubleNumber);
        printArray(arr);

        std::ranges::for_each(arr, halfNumber);     // std::ranges ... c++20 features!!!
        printArray(arr);

        std::for_each(std::next(arr.begin()), arr.end(), doubleNumber);
        printArray(arr);
    }

    return 0;
}
