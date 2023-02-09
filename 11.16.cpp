#include <iostream>
#include <array>

template <typename T, size_t num>
void printArray(const std::array<T, num> &myArray)
{
    for (auto element : myArray) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

int main()
{
    {
        std::array myDoubleArray5{ 9.0, 7.2, 5.4, 3.6, 1.8 };
        printArray(myDoubleArray5);

        std::array myIntArray7{ 3, 1, 4, 2, 6, 9, 5 };
        printArray(myIntArray7);
    }

    {
        std::array myArray { 7, 3, 1, 9, 5 };

        // Iterate through the array and print the value of the elements
        for (size_t i{ 0 }; i < myArray.size(); ++i)
            std::cout << myArray[i] << ' ';

        std::cout << '\n';
    }

    {
        std::array myArray { 7, 3, 1, 9, 5 };
        for (auto i{ myArray.size() }; i-- > 0;) {
            std::cout << myArray[i] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
