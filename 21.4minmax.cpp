#include <iostream>
#include <list>
#include <numeric>
#include <algorithm>

int main()
{
    std::list<int> li(6);
    std::iota(li.begin(), li.end(), 0);

    std::cout << *std::min_element(li.cbegin(), li.cend()) << ' ';
    std::cout << *std::max_element(li.cbegin(), li.cend()) << '\n';

    return 0;
}
