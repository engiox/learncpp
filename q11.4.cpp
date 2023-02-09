#include <iostream>
#include <iterator>

void q1();
void q2();
void q3();
void q4();

int main()
{
    std::cout << "****** Q2 ******\n";
    q2();

    std::cout << "****** Q3 ******\n";
    q3();

    return 0;
}

void q1() {}

void q2()
{
    {
        int array[]{ 30, 50, 20, 10, 40 };
        constexpr int length{ static_cast<int>(std::size(array)) };

        // Step through each element of the array
        // (except the last one, which will already be sorted by the time we get there)
        for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
        {
            // smallestIndex is the index of the smallest element we’ve encountered this iteration
            // Start by assuming the smallest element is the first element of this iteration
            int smallestIndex{ startIndex };

            // Then look for a smaller element in the rest of the array
            for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
            {
                // If we've found an element that is smaller than our previously found smallest
                if (array[currentIndex] < array[smallestIndex])
                    // then keep track of it
                    smallestIndex = currentIndex;
            }

            // smallestIndex is now the smallest element in the remaining array
            // swap our start element with our smallest element (this sorts it into the correct place)
            std::swap(array[startIndex], array[smallestIndex]);
        }

        // Now that the whole array is sorted, print our sorted array as proof it works
        for (int index{ 0 }; index < length; ++index)
            std::cout << array[index] << ' ';

        std::cout << '\n';
    }
    {
        int array[]{ 30, 50, 20, 10, 40 };
        constexpr int length{ static_cast<int>(std::size(array)) };

        // Step through each element of the array
        // (except the last one, which will already be sorted by the time we get there)
        for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
        {
            // smallestIndex is the index of the smallest element we’ve encountered this iteration
            // Start by assuming the smallest element is the first element of this iteration
            int largestIndex{ startIndex };

            // Then look for a smaller element in the rest of the array
            for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
            {
                // If we've found an element that is smaller than our previously found smallest
                if (array[currentIndex] > array[largestIndex])
                    // then keep track of it
                    largestIndex = currentIndex;
            }

            // smallestIndex is now the smallest element in the remaining array
            // swap our start element with our smallest element (this sorts it into the correct place)
            std::swap(array[startIndex], array[largestIndex]);
        }

        // Now that the whole array is sorted, print our sorted array as proof it works
        for (int index{ 0 }; index < length; ++index)
            std::cout << array[index] << ' ';

        std::cout << '\n';
    }
}

void q3()
{
    int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
    constexpr int length{ std::ssize(array) };
    bool swapped{ false };

    for (int endIndex{ length }; endIndex > 0; --endIndex) {
        swapped = false;
        for (int currentIndex{ 0 }; currentIndex < endIndex - 1; ++ currentIndex) {
            if (array[currentIndex] > array[currentIndex + 1]) {
                std::swap(array[currentIndex], array[currentIndex + 1]);
                swapped = true;
            }
            for (int index{ 0 }; index < length; ++index) {
                std::cout << array[index] << (currentIndex == index ? '=' : ' ');
            }
            std::cout << " : " << (swapped ? 'T' : 'F') << '\n';
        }
        if (swapped == false) break;
    }
//   for (int index{ 0 }; index < length; ++index)
//       std::cout << array[index] << ' ';
//   std::cout << '\n';
}

void q4()
{
}
