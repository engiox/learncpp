#include <iostream>
#include <iterator>

int *findValue(int *pBegin, int *pEnd, int val)
{
    for (int *pIndex{ pBegin }; pIndex < pEnd - 1; ++pIndex) {
        if (*pIndex == val) return pIndex;
    }
    return pEnd;
}

int main()
{
    int arr[]{ 2, 5, 4, 10, 8, 20, 16, 40 };

    int *found{ findValue(std::begin(arr), std::end(arr), 20) };

    if (found != std::end(arr)) {
        std::cout << *found << " @ " << found << " : "
                  << found - std::begin(arr) << '\n';
    }

    return 0;
}
