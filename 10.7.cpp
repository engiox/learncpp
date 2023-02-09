#include <iostream>

struct Something
{
    double x;
    int y {};
    int z { 2 };
};

int main()
{
    Something s1;

    std::cout << s1.x << s1.y << s1.z << '\n';
    std::cout << sizeof(s1.x) << sizeof(s1.y) << sizeof(s1.z) << '\n';

    return 0;
}
