#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vect{ 7, -3, 6, 2, -5, 0, 4 };
    std::cout << "Original:\n";
    for (auto i : vect) std::cout << i << ' ';
    std::cout << "\n\n";

    std::sort(vect.begin(), vect.end());
    std::cout << "sort():\n";
    for (auto i : vect) std::cout << i << ' ';
    std::cout << "\n\n";

    std::sort(vect.begin(), vect.end(), std::greater());
    std::cout << "sort(greater):\n";
    for (auto i : vect) std::cout << i << ' ';
    std::cout << "\n\n";

    std::reverse(vect.begin(), vect.end());
    std::cout << "reverse():\n";
    for (auto i : vect) std::cout << i << ' ';
    std::cout << "\n\n";

    std::reverse(vect.begin(), vect.end());
    std::cout << "reverse():\n";
    for (auto i : vect) std::cout << i << ' ';
    std::cout << "\n\n";

    std::sort(vect.begin(), vect.end(), std::less());
    std::cout << "sort(less):\n";
    for (auto i : vect) std::cout << i << ' ';
    std::cout << "\n\n";

    return 0;
}
