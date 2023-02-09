#include <array>
#include <bits/ranges_algo.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>

void printInt(int item)
{
    std::cout << item << ' ';
}

template <typename T, size_t num>
void printArray(const std::array<T, num> &arr)
{
    for (auto i : arr) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main()
{
    std::array arr{ 1, 2, 3, 4, 5, 6 };

    std::cout << std::reduce(arr.cbegin(), arr.cend()) << '\n';
    std::cout << std::accumulate(arr.cbegin(), arr.cend(), 0) << '\n';
    printArray(arr);

    std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(arr.begin(), arr.end(), mt);
    printArray(arr);
    std::shuffle(arr.begin(), arr.end(), mt);
    std::ranges::for_each(arr, printInt);
    std::cout << '\n';

    return 0;
}
