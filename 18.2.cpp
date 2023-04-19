#include <iostream>
#include <string>
#include <string_view>

class Animal
{
protected:
    std::string m_name;

    Animal(const std::string_view name) : m_name{ name } {}
    virtual ~Animal() = default;

public:
    const std::string& getName() const { return m_name; }
    virtual const std::string_view speak() const { return "???"; }
};

class Cat : public Animal
{
public:
    Cat(const std::string_view name) : Animal{ name } {}
    const std::string_view speak() const { return "Mew"; }
};

class Dog : public Animal
{
public:
    Dog(const std::string_view name) : Animal{ name } {}
    const std::string_view speak() const { return "Woof"; }
};

void report(const Animal& anim)
{
    std::cout << anim.getName() << " says " << anim.speak() << '\n';
}

int main()
{
    Cat cat{ "Fred" };
    Dog dog{ "Garbo" };

    report(cat);
    report(dog);

    return 0;
}
