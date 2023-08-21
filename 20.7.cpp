#include <iostream>

class A
{
    int m_x;

public:
    A(int x) : m_x{ x } {}
};

class B : public A
{
public:
    B(int x) try : A{x}
    {
        if (x <= 0)
            throw 1;
    }
    catch (...)
    {
        std::cerr << "Exception caught\n";
    }
    ~B() try
    {
        throw 2;
    } catch (...) {
        std::cerr << "Exception caught in ~B()\n";
    }
};

int main()
{
    try {
        B b{ 0 };
    }
    catch (int) {
        std::cout << "Oops\n";
    }

    try {
        B b1{ 3 };
    } catch (int) {
        std::cout << "Oppes in ~B()\n";
    }
 
    return 0;
}
