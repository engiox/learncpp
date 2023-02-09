#include <ios>
#include <iostream>
#include <iterator>
#include <limits>

void q1();
void q2();
void q3();
void q3a();

int main()
{
    std::cout << "*** Q1 ***\n";
    q1();

    std::cout << "*** Q2 ***\n";
    q2();

    std::cout << "*** Q3 ***\n";
    q3();

    std::cout << "*** Q3A ***\n";
    q3a();

    return 0;
}

void q1()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };

    for (int i{}; i < std::ssize(array); ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';
}

void q2()
{
    constexpr int array[]{ 4, 6, 7, 3, 8, 2, 1, 9, 5 };

    int choice {};
    do {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > 9);

    for (int i{}; i < std::ssize(array); ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << '\n';

    for (int i{}; i < std::ssize(array); ++i) {
        std::cout << "Comparing with value " << array[i] << " @ index " << i << '\n';
        if (choice == array[i]) {
            std::cout << "The number " << choice << " has index " << i << '\n';
            break;
        }
    }
}

void q3()
{
    constexpr int scores[]{ 84, 92, 76, 81, 56 };

//    int maxScore{ 0 }; // Assume our largest score is 0 to start
    int maxIndex{};

    // now look for a larger score in the full array
    for (int student{ 0 }; student < static_cast<int>(std::size(scores)); ++student)
    {
        if (scores[student] >= scores[maxIndex])
        {
            maxIndex = student;
        }
    }

    std::cout << "The best score was " << scores[maxIndex] << '\n';
}

void q3a()

{
    constexpr int scores[]{ 84, 92, 76, 81, 56 };

    int maxIndex{ 0 }; // Assume the element at index 0 is the largest

    // now look for a larger score in the rest of the array
    for (int student{ 1 }; student < static_cast<int>(std::size(scores)); ++student)
    {
        if (scores[student] > scores[maxIndex])
        {
            maxIndex = student;
        }
    }

    std::cout << "The best score was " << scores[maxIndex] << '\n';
}

