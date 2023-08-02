#include <iostream>
#include <string_view>
#include <vector>
#include <functional>

class Base
{
protected:
    int m_value{};

public:
    Base(int value)
        : m_value{ value }
    {
    }

    virtual std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived: public Base
{
public:
    Derived(int value)
        : Base{ value }
    {
    }

   std::string_view getName() const override { return "Derived"; }
};

int main()
{
    std::vector<std::reference_wrapper<Base>> v{};
    Base b{ 5 };
    Derived d{ 6 };

    v.push_back(b);
    v.push_back(d);

    for (const auto& elem : v)
        std::cout << "I am a " << elem.get().getName()
                  << " with value " << elem.get().getValue() << '\n';

    Derived d1{ 5 };
    Derived d2{ 6 };
    Base& b1{ d1 };

    Base b2{ d2 };
    Derived d3{ b };

    b = d1;

    return 0;
}
