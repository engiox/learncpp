#include <functional>
#include <iostream>
#include <typeinfo>
#include <iomanip>
#include <string_view>
#include <cstring>
#include <array>
#include <algorithm>

bool containsNut(std::string_view str)
{
    return (str.find("nut") != std::string_view::npos);
}

// We don't know what fn will be. std::function works with regular functions and lambdas.
void repeat(int repetitions, const std::function<void(int)>& fn)
{
    std::cout << std::setw(28) << "std::function<void(int>& : " << std::setw(18)
              << typeid(fn).name() << " : ";
    for (int i{ 0 }; i < repetitions; ++i) {
        fn(i);
    }
}

void repeatL(int repetitions, auto fn)
{
    std::cout << std::setw(28) << "auto : " << std::setw(18)
              << typeid(fn).name() << " : ";
    for (int i{ 0 }; i < repetitions; ++i) {
        fn(i);
    }
}

bool UDFGreater(int a, int b)
{
    return (a > b);
}

int main()
{
    {
        using namespace std::literals;
        std::array<std::string_view, 4> arr1{ "apple", "banana", "walnut", "lemon" };
        std::array arrl{ "strawberry"sv, "orange"sv, "grape"sv, "kiwi"sv };

        auto found{ std::find_if(arr1.begin(), arr1.end(), containsNut) };
        if (found == arr1.end()) {
            std::cout << "No nuts\n";
        } else {
            std::cout << "Found " << *found << '\n';
        }

        found = std::find_if(arrl.begin(), arrl.end(), containsNut);
        if (found == arrl.end()) {
            std::cout << "No nuts\n";
        } else {
            std::cout << "Found " << *found << '\n';
        }

        found = std::find_if(arrl.begin(), arrl.end(), [](std::string_view str){
                    return (str.find("rape") != std::string_view::npos); });
        if (found == arrl.end()) {
            std::cout << "No nuts\n";
        } else {
            std::cout << "Found " << *found << '\n';
        }
    }

    ////////// Type of a Lambda
    {
        // A regular function pointer. ONLY Works with an empty capture clause([])
        double (*addNumbers1)(double, double){
            [](double a, double b) { return (a + b); } };
        addNumbers1(3, 3.5);

        // Using std::function. The lambda could have a NON-Empty capture clause
        // pre-C++17 --> std::function<double(double, double)> addNumbers2
        std::function addNumbers2 {
            [](double a, double b) { return (a + b); } };
        addNumbers2(3, 3.5);

        // Using auto. Stores the lambda with its REAL type.
        auto addNumbers3 {
            [](double a, double b) { return (a + b); } };
        addNumbers3(3, 3.5);
    }

    {
        repeat(3, [](int i) { std::cout << i << ' '; });
        std::cout << '\n';
        repeatL(3, [](int i) { std::cout << i*2 << ' '; });
        std::cout << '\n';
    }

    ////////// Generic Lambdas
    {
        constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
            "January",
            "February",
            "March",
            "April",
            "May",
            "June",
            "July",
            "August",
            "September",
            "October",
            "November",
            "December"
        };

        // Search for two consecutive months that start with the same letter.
        const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
                [](const auto& a, const auto& b) {
                return (a[0] == b[0]);
                }) };

        // Make sure that two months were found.
        if (sameLetter != months.end())
        {
            // std::next returns the next iterator after sameLetter
            std::cout << *sameLetter << " and " << *std::next(sameLetter)
                << " start with the same letter\n";
        }

        // EXERCISE : compare string length
        const auto sameLength1{ std::adjacent_find(months.begin(), months.end(),
                [](const auto& a, const auto& b) {
                return (strlen(a) == strlen(b)); //a[0] == b[0]);
                }) };
        if (sameLength1 != months.end()) {
            std::cout << *sameLength1 << " and " << *std::next(sameLength1)
                << " have the same length\n";
        }
        const auto sameLength2{ std::adjacent_find(std::next(sameLength1), months.end(),
                [](std::string_view a, std::string_view b) {
                return (a.size() == b.size());
                }) };
        if (sameLength2 != months.end()) {
            std::cout << *sameLength2 << " and " << *std::next(sameLength2)
                << " have the same length\n";
        }
    }

    // Standard Librafy Function Objects
    {
        std::array arr{ 13, 90, 99, 5, 40, 80 };

        std::sort(arr.begin(), arr.end(), UDFGreater);

        for (auto i : arr) {
            std::cout << i << ' ';
        }
        std::cout << '\n';

        std::sort(arr.begin(), arr.end(), std::less{});
        for (auto i : arr) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
