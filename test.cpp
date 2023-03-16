#include <iostream>
#include <typeinfo>

int comp(int a, int b)
{
    return ( a > b ? (std::cout << "Former is larger: ", a)
                   : (std::cout << "Latter is larger: ", b) );
}
int main()
{
    const int bit16{ 65535 };
    const int& ref{ bit16 };
    
    std::cout << typeid(bit16).name() << '\n';
    std::cout << typeid(ref).name() << '\n';

    std::cout << comp << '\n';
    std::cout << comp(6, 3) << '\n';
    std::cout << comp(3, 8) << '\n';

    [](int n){
        for (int i = 0; i < n; ++i) {
            std::cout << "Loud ";
        }
        std::cout << '\n';
    }(6);

    return 0;
}
