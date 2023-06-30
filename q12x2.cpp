#include <iostream>

void a() {}
void b() {}
void c() {}

void d()
{
    int array[100000000]{};
    for (auto x : array) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

void e() {}

int main()
{
    a();
    b();
    c();
    d();
    e();

    return 0;
}
