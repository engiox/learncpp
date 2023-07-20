#include <iostream>
#include <string_view>

class Base
{
public:
    virtual ~Base() = default;
    virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
    void printType() { std::cout << "returned a Base\n"; }
    virtual void printVirtualType() { std::cout << "virtual returned a Base\n"; }
};

class Derived : public Base
{
public:
    virtual ~Derived() = default;
    virtual Derived* getThis() { std::cout << "called Derived::getThis()\n"; return this; }
    void printType() { std::cout << "returned a Derived\n"; }
    virtual void printVirtualType() { std::cout << "virtual returned a Derived\n"; }
};

int main()
{
    Derived d{};
    Base* b{ &d };
    d.getThis()->printType();
    b->getThis()->printType();
    b->getThis()->printVirtualType();

    return 0;
}
