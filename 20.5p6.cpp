#include <iostream>
#include <iomanip>

class Base
{
public:
    Base() { std::cout << std::setw(22) << "Base created @ " << this << '\n'; }
    ~Base() { std::cout << std::setw(22) << "Base destroyed @ " << this << '\n'; }
    Base(const Base& org) { std::cout << std::setw(22) << "Base copy @ " << this << '\n'; }
};

class Derived : public Base
{
public:
    Derived() { std::cout << std::setw(22) << "Derived created @ " << this << '\n'; }
    ~Derived() { std::cout << std::setw(22) << "Derived destroyed @ " << this << '\n'; }
    Derived(const Derived& org) : Base()
        { std::cout << std::setw(22) << "Derived copy @ " << this << '\n'; }
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

    std::cout << "Ending program\n";

    return 0;
}
