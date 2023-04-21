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

    std::vector<int> vi{};
    vi.push_back(1);
    vi.push_back(3);

    return 0;
}
