#include <iostream>
#include <typeinfo>

int comp(int a, int b)
{
    return ( a > b ? std::cout << "Former is larger\n", a : b );
}
int main()
{
    const int bit16{ 65535 };
    const int& ref{ bit16 };
    
    std::cout << typeid(bit16).name() << '\n';
    std::cout << typeid(ref).name() << '\n';

    std::cout << comp;
    std::cout << comp(6, 3) << '\n';

    return 0;
}
