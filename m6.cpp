#include <iostream>
#include <memory>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

void p1()
{
    std::unique_ptr<Resource> res1{ new Resource };
    std::unique_ptr<Resource> res2{};

    std::cout << "res1 is " << (res1 ? "not null" : "null" ) << '\n';
    std::cout << "res2 is " << (res2 ? "not null" : "null" ) << '\n';

    res2 = std::move(res1);
    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (res1 ? "not null" : "null" ) << '\n';
    std::cout << "res2 is " << (res2 ? "not null" : "null" ) << '\n';
}

class Fraction
{
    int m_numerator{};
    int m_denominator{};
public:
    Fraction(int num = 0, int den = 1) : m_numerator{num}, m_denominator{den} {}
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f1)
    {
        os << f1.m_numerator << '/' << f1.m_denominator;
        return os;
    }
};

void p2()
{
    auto f1{ std::make_unique<Fraction>(3, 5) };
    std::cout << *f1 << '\n';

    auto f2{ std::make_unique<Fraction[]>(4) };
    std::cout << f2[0] << '\n';

    std::unique_ptr<Fraction> f3{ new Fraction(3, 5) };
    std::cout << *f3 << '\n';
    std::unique_ptr<Fraction[]> f4{ new Fraction[4] };
    std::cout << f4[0] << '\n';
}

int main()
{
    p1();
    p2();

    return 0;
}
