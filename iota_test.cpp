#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main()
{
    std::vector<int> vi(10);
    std::iota(vi.begin(), vi.end(), 1);

    for (auto val : vi)
        std::cout << val << ' ';

    std::cout << "\nnow floating...\n"; 

    std::vector<float> vf(10);
    std::iota(vf.begin(), vf.end(), 0.6);

    for (auto val : vf)
        std::cout << val << ' ';

    return 0;
}
