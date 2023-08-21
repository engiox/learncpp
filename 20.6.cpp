#include <iostream>
#include <iomanip>

class Base
{
public:
    Base() { std::cout << std::setw(22) << "Base construct @ " << this << '\n'; }
    Base(const Base& b) { std::cout << std::setw(22) << "Base copy construct @ " << this << '\n'; }
    ~Base() { std::cout << std::setw(22) << "Base destruct @ " << this << '\n'; }
    virtual void print() { std::cout << "Base"; }
};

class Derived: public Base
{
public:
    Derived() { std::cout << std::setw(22) << "Derived construct @ " << this << '\n'; }
    Derived(const Derived& d) : Base()
        { std::cout << std::setw(22) << "Derived copy construct @ " << this << '\n'; }
    ~Derived() { std::cout << std::setw(22) << "Derived destruct @ " << this << '\n'; }
    void print() override { std::cout << "Derived"; }
};

int main()
{
    try
    {
        try
        {
            throw Derived{};
        }
        catch (Base& b)
        {
            std::cout << "Caught Base b, which is actually a ";
            b.print();
            std::cout << '\n';
            throw;  // throw b; // the Derived object gets sliced here
        }
    }
    catch (Base& b)
    {
        std::cout << "Caught Base b, which is actually a ";
        b.print();
        std::cout << '\n';
    }

    return 0;
}
