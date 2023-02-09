#include <iostream>


int main()
{
    {
        struct Foo
        {
            short a {};
            int b {};
            double c {};
        };
        std::cout << "The size of short is " << sizeof(short) << '\n';
        std::cout << "The size of int is " << sizeof(int) << '\n';
        std::cout << "The size of double is " << sizeof(double) << '\n';
        std::cout << "The size of Foo (s, i, d) is " << sizeof(Foo) << '\n';
    }
    std::cout << '\n';

    {
        struct Foo1
        {
            short a{};
            short qq{}; // note: qq is defined here
            int b{};
            double c{};
        };

        struct Foo2
        {
            short a{};
            int b{};
            double c{};
            short qq{}; // note: qq is defined here
        };
        std::cout << "The size of Foo1 (s, s, i, d) is " << sizeof(Foo1) << '\n';
        std::cout << "The size of Foo2 (s, i, d, s) is " << sizeof(Foo2) << '\n';
    }
    std::cout << '\n';

    return 0;
}
