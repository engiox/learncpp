#include <iostream>
#include <memory>
#include <ostream>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    friend std::ostream& operator<<(std::ostream& os, const Resource& rsc) {
        os << "I am a resource";
        return os;
    }
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

auto createResource()
{
    return std::make_unique<Resource>();
}

void takeOwnership(std::unique_ptr<Resource> rsc)
{
    if (rsc)
        std::cout << *rsc << '\n';
}

void p3()
{
    auto ptr{ std::make_unique<Resource>() };

    takeOwnership(std::move(ptr));

    std::cout << "Ending program\n";
}

void useResource(Resource* rsc)
{
    if (rsc)
        std::cout << *rsc << '\n';
    else
        std::cout << "No resource\n";
}

void p4()
{
    auto ptr{ std::make_unique<Resource>() };
    
    useResource(ptr.get());
    
    std::cout << "Ending program\n";
}

int main()
{
    p1();
    p2();
    p3();
    p4();

    return 0;
}
