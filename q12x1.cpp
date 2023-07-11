#include <iostream>

//double max(double a, double b) { return a > b ? a : b; }
const double& max(const double& a, const double& b) { return a > b ? a : b; }

void swap(int &a, int &b) { int tmp = b; b = a; a = tmp; }

int& getLargestElement(int *arr, int length);
// define function body of getLargestElement()

int& getLargestElement(int *arr, int length)
{
    int largest{0};

    for (int idx{1}; idx < length; ++idx) {
        std::cout << arr[largest] << ' ' << arr[idx] << '\n';
        if (arr[idx] >= arr[largest]) {
            largest = idx;
        }
    }
    return arr[largest];
}

int main()
{
    std::cout << max(3.3, 6.6) << '\n';

    int n1{ 5 }, n2{ 2 };
    swap(n1, n2);
    std::cout << n1 << ' ' << n2 << '\n';

    int intArray[]{ 3, 5, 1, 6, 0, 7 };
    std::cout << sizeof(intArray) << ' ' << std::size(intArray) <<  '\n';
    std::cout << getLargestElement(intArray, std::size(intArray)) << '\n';

    return 0;
}
