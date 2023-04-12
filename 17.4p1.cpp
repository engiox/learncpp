#include <iostream>

class Base
{
public:
    int m_id {};

    Base(int id=0)
        : m_id{ id }
    {
        std::cout << "Base constructor\n";
    }

    int getId() const { return m_id; }
};

class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0, int id=0)
        : m_cost{ cost }, Base{ id } // Call Base(int) constructor with value id!
//        , m_cost{ cost }
    {
        std::cout << "Derived constructor\n";
    }

    double getCost() const { return m_cost; }
};

int main()
{
    Derived derived{ 1.3, 5 }; // use Derived(double, int) constructor
    std::cout << "Id: " << derived.getId() << '\n';
    std::cout << "Cost: " << derived.getCost() << '\n';

    return 0;
}
