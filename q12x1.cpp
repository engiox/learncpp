#include <iostream>

double max(double a, double b) { return a > b ? a : b; }
void swap(int &a, int &b) { int tmp = b; b = a; a = tmp; }
int &getLargestElement(int *arr, int length);

int main()
{
    std::cout << max(3.3, 6.6) << '\n';

    int n1{ 5 }, n2{ 2 };
    swap(n1, n2);
    std::cout << n1 << ' ' << n2 << '\n';

    return 0;
}
