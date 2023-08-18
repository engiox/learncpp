#include <iostream>

class Base
{
public:
    Base() { std::cout << "Base created\n"; }
    ~Base() { std::cout << "Base destroyed\n"; }
};

class Derived : public Base
{
public:
    Derived() { std::cout << "Derived created\n"; }
    ~Derived() { std::cout << "Derived destroyed\n"; }

//    Derived(const Derived&) = delete; // not copyable
};

int main()
{
    std::cout << "Beginning program\n";
    Derived d{};
    std::cout << "Derived d created\n";

    try
    {
        std::cout << "throwing d...\n";
        throw d; // compile error: Derived copy constructor was deleted
        std::cout << "throwed d!\n";
    }
    catch (const Derived& derived)
    {
        std::cerr << "caught Derived\n";
    }
    catch (const Base& base)
    {
        std::cerr << "caught Base\n";
    }

    return 0;
}
