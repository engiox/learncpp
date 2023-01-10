#include <iostream>

// Evaluates to true if the type (or object) uses 2 or fewer memory addresses worth of memory
#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

struct S
{
    double a, b, c;
};

int main()
{
    std::cout << std::boolalpha; // print true or false rather than 1 or 0
    std::cout << isSmall(int) << '\n'; // true
    std::cout << isSmall(double) << '\n'; // true
    std::cout << isSmall(S) << '\n'; // false

    return 0;
}
