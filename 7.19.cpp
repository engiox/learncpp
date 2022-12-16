#include <iostream>
#include <random>
#include <chrono>

void func1();
void func2();
void func3();
void func4();
void func5();
void func6();
void func7();

int main()
{
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();

    return 0;
}

void func1()
{
    std::cout << "\nStarting func01()...\n";

    std::mt19937 mt;
//    std::cout << "size of mt = " << sizeof(mt) << '\n';
//    std::cout << "mt = " << mt << '\n';

    for (int count{1}; count <= 40; ++count) {
        std::cout << mt() << '\t';

        if (count % 5 == 0)
            std::cout << '\n';
    }
//    std::cout << "Finished func01()...\n";
}

void func2()
{
    std::cout << "\nStarting func02()...\n";

    std::mt19937 mt;
    std::uniform_int_distribution<> die6{ 1, 6 };

    for (int count{ 1 }; count <= 40; ++count) {
        std::cout << die6(mt) << '\t';
        if (count % 10 == 0)
            std::cout << '\n';
    }
}

void func3()
{
    std::cout << "\nStarting func03()...\n";

    std::mt19937 mt{ static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()
        ) };
    std::uniform_int_distribution<> die6{ 1, 6 };

    for (int count{ 1 }; count <= 40; ++count) {
        std::cout << die6(mt) << '\t';

        if (count % 10 == 0)
            std::cout << '\n';
    }
}

void func4()
{
    std::cout << "\nStarting func04()...\n";
}

void func5()
{
    std::cout << "\nStarting func05()...\n";
}

void func6()
{
    std::cout << "\nStarting func06()...\n";
}

void func7()
{
}
