#include <iostream>
#include <memory>
#include <string>

class Person
{
    std::string m_name;
//    std::shared_ptr<Person> m_partner;
    std::weak_ptr<Person> m_partner;
public:
    Person(const std::string& name) : m_name{ name } {
        std::cout << m_name << " created\n";
    }
    ~Person() { std::cout << m_name << " destroyed\n"; }
    friend bool partnerUp(std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2) {
        if (!p1 || !p2)
            return false;
        p1->m_partner = p2;
        p2->m_partner = p1;
        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';
        return true;
    }
    const std::shared_ptr<Person> getPartner() const { return m_partner.lock(); }
    const std::string& getName() const { return m_name; }
};

class Resource
{
public:
//    std::shared_ptr<Resource> m_ptr;
    std::weak_ptr<Resource> m_ptr;
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

auto getWeakPtr()
{
    auto ptr{ std::make_shared<Resource>() };
    return std::weak_ptr<Resource>(ptr);
}

auto getDumbPtr()
{
    auto ptr{ std::make_unique<Resource>() };
    return ptr.get();
}

int main()
{
    auto lucy{ std::make_shared<Person>("Lucy") };
    auto rick{ std::make_shared<Person>("Rick") };

    partnerUp(lucy, rick);

    auto partner{ rick->getPartner() };
    std::cout << rick->getName() << "'s partner is " << partner->getName() << '\n';

    auto ptr{ std::make_shared<Resource>() };
    ptr->m_ptr = ptr;

    auto dumb{ getDumbPtr() };
    std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

    auto weak{ getWeakPtr() };
    std::cout << "Our weak ptr is: " << (weak.expired() ? "nullptr\n" : "non-null\n");

    return 0;
};
