#include <iostream>
#include <iomanip>
#include <vector>

class MyClass
{
    public:
        static std::vector<char> s_mychars;
};

std::vector<char> MyClass::s_mychars{[]()
    {
        std::vector<char> v;
        for (char ch{'a'}; ch <= 'z'; ++ch) {
            v.push_back(ch);
        }
        return v;
    } ()
};

int main()
{
    std::vector<int> vInt1{0, 1, 2, 3, 4, 5, 6};
    std::vector<int> vInt2{[]()
        {
            std::vector<int> v2;
            for (int i{0}; i < 100; ++i) {
                v2.push_back(i);
            }
            return v2;
        }() };

    for (auto idx:vInt1) {
        std::cout << vInt1[idx] << ' ';
    }
    std::cout << '\n';

    for (auto idx:vInt2) {
        std::cout << vInt2[idx] << ' ';
    }
    std::cout << '\n';

    return 0;
}
