#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>

int main()
{
    std::list<int> li(6);
    std::iota(li.begin(), li.end(), 0);

    std::list<int>::const_iterator it{ std::find(li.cbegin(), li.cend(), 3) };

    li.insert(it, 8);

    for (auto i : li)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
