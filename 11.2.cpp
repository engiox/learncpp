#include <iostream>
#include <iterator>

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

//void printArrSize(int arr[])
//{
//    std::cout << std::size(arr) << '\n';
//}

void printSize(int arr[])
{
    std::cout << sizeof(arr) << ',' << sizeof(arr[0]) << " = ";
    std::cout << "pointer : " << sizeof(arr) << ", " << "int : " << sizeof(int) << '\n';
    std::cout << sizeof(arr) / sizeof(arr[0]) << '\n';
}

int main()
{
    {
        int prime[5] { 2, 3, 5, 7, 11 };
        int fibbo[5] = { 1, 2, 3, 5, 8 };
        int intar[5];
        double darr[5];

        for (int i {0}; i < 5; ++i) {
            if (prime[i] == fibbo[i])
                std::cout << "Match!\n";
            else
                std::cout << "No Match!\n";
            std::cout << intar[i] << '\n';
            std::cout << darr[i] << '\n';
        }
    }

    {
        int testScores[max_students]{}; // allocate 5 integers
        testScores[stan] = 76;
    }

    {
        int arr[] { 3, 1, 4, 1, 5, 9, 2 };
        std::cout << std::size(arr) << '\n';
        std::cout << sizeof(arr) / sizeof(arr[0]) << '\n';
    }

    {
        int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
        std::cout << sizeof(array) / sizeof(array[0]) << '\n';
        printSize(array);
    }

    {
        int prime[5]{}; // hold the first 5 prime numbers
        prime[5] = 13;
        std::cout << prime[5] << "!\n";
    }

    return 0;
}
