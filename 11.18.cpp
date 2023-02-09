#include <vector>
#include <array>
#include <cstddef>
#include <iostream>

int main()
{
    {
        // In C++17, the type of variable data is deduced to std::array<int, 7>
        // If you get an error compiling this example, see the warning below
        std::array data{ 0, 1, 2, 3, 4, 5, 6 };
        std::size_t length{ std::size(data) };

        // while-loop with explicit index
        std::size_t index{ 0 };
        while (index < length)
        {
            std::cout << data[index] << ' ';
            ++index;
        }
        std::cout << '\n';

        // for-loop with explicit index
        for (index = 0; index < length; ++index)
        {
            std::cout << data[index] << ' ';
        }
        std::cout << '\n';

        // for-loop with pointer (Note: ptr can't be const, because we increment it)
        for (auto ptr{ &data[0] }; ptr != (&data[0] + length); ++ptr)
        {
            std::cout << *ptr << ' ';
        }
        std::cout << '\n';

        // ranged-based for loop
        for (int i : data)
        {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
    // Pointers as an iterator
    {
        std::array data{ 0, 1, 2, 3, 4, 5, 6 };
        auto begin{ &data[0] };
        auto end{ begin + std::size(data) };
        std::cout << "begin: " << begin << ", " << "end: " << end << '\n';
        for (auto ptr{ begin }; ptr != end; ++ptr) {
            std::cout << *ptr << ' ';
        }
        std::cout << &data[std::size(data)];    // UNDEFINED! operator& accesses out of range data
        std::cout << '\n';
    }
    // Standard library iterators
    {
        {   // C++ Standard library container - member functions
            std::array data{ 1, 2, 3 };
            auto begin{ data.begin() };
            auto end{ data.end() };
            std::cout << "begin: " << begin << ", " << "end: " << end << '\n';
            for (auto ptr{ begin }; ptr != end; ++ptr) {
                std::cout << *ptr << ' ';
            }
            std::cout << &data[std::size(data)];    // UNDEFINED! operator& accesses out of range data
            std::cout << '\n';
        }
        {   // C-style array - std::begin(array) & std::end(array)
            // #include <iterator>
            int array[]{ 1, 2, 3 };
            auto begin{ std::begin(array) };
            auto end{ std::end(array) };
            std::cout << "C array begin: " << begin << ", " << "end: " << end << '\n';
            for (auto ptr{ begin }; ptr != end; ++ptr) {
                std::cout << *ptr << ' ';
            }
        }
    }
    // Iterator invalidation (dangling iterators)
    {
        std::vector v{ 1, 2, 3, 4, 5, 6 };
        std::cout << "v.size(): " << v.size() << '\n';
        auto it{ v.begin() };
        std::cout << *(++it) << '\n';
        v.erase(it);
        std::cout << "v.size(): " << v.size() << '\n';
        std::cout << *it << '\n';
        std::cout << *(--it) << '\n';
    }

    return 0;
}
