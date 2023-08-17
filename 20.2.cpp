#include <iostream>

void examine(int val)
{
    std::cout << "examining " << val << "...\n";
    if (val < 0)
        throw -1;
    if (val == 0)
        throw 0;
    if (val > 0)
        throw 1;
}

void p1()
{
    try {
        for (int i{-3}; i < 3; ++i) {
            examine(i);
        }
    }
    catch (int err) {
        if (err == -1) std::cout << "negative\n";
        if (err == 0) std::cout << "zero\n";
        if (err == 1) std::cout << "positive\n";
    }
}

void p2()
{
    try {
        throw -1;
        throw 'x';
        throw 3.1;
        throw "cstring";
    }
    catch (double y) {
        std::cerr << "caught an double exception with value: " << y << '\n';
    }
    catch (int x) {
        std::cerr << "caught an int exception with value: " << x << '\n';
    }
    catch (const std::string& z) {
        std::cerr << "caught an std::string exception with value: " << z << '\n';
    }
    std::cout << "inspection finished\n";
}

int main()
{
    std::cout << "====== p1() ======\n";
    p1();
    std::cout << "====== p2() ======\n";
    p2();
    return 0;
}
