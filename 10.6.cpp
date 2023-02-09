#include <iostream>

struct Employee
{
    int id;
    int age;
    double wage;
};

struct Foo
{
    int a{};
    int b{};
    int c{};
};

int main()
{
    Employee joe{};
    std::cout << joe.id << '\n';

    Foo f1{ .a{1}, .c{3} };
//    Foo f2{ .b{2}, .a{1} };
    std::cout << f1.a << f1.b << f1.c << '\n';
//    std::cout << f2.a << f2.b << f2.c << '\n';

    return 0;
}
