#include <string_view>
#include <iostream>
#include <array>

class Base
{
protected:
    int m_value{};

public:
    Base(int val) : m_value{ val } {}
    std::string_view getName() const { return "Base"; }
    int getValue() const { return m_value; }
};

class Derived : public Base
{
public:
    Derived(int val) : Base{ val } {}
    std::string_view getName() const { return "Derived"; }
    int getValueDoubled() const { return m_value * 2; }
};

void p1()
{
    Derived derived{ 5 };
    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';

    Derived& rDerived{ derived };
    std::cout << "rDerived is a " << rDerived.getName() << " and has value " << rDerived.getValue() << '\n';

    Derived* pDerived{ &derived };
    std::cout << "pDerived is a " << pDerived->getName() << " and has value " << pDerived->getValue() << '\n';
}

void p2()
{
    Derived derived{ 5 };

    Base& rBase{ derived };
    Base* pBase{ &derived };

    std::cout << "derived is a " << derived.getName() << " and has value " << derived.getValue() << '\n';
    std::cout << "rBase is a " << rBase.getName() << " and has value " << rBase.getValue() << '\n';
    std::cout << "pBase is a " << pBase->getName() << " and has value " << pBase->getValue() << '\n';
}

class Animal
{
protected:
    std::string m_name;
    std::string m_speak;
    Animal(std::string_view name) : m_name{ name } {}
    Animal(std::string_view name, std::string_view speak) : m_name{ name }, m_speak{ speak } {}
    Animal(const Animal&) = default;
    Animal& operator=(const Animal&) = default;
public:
    std::string_view getName() const { return m_name; }
    std::string_view speak() const { return m_speak; }
};

class Cat : public Animal
{
public:
    Cat(std::string_view name) : Animal{ name, "Meow" } {}
    std::string_view speak() const { return m_speak; }
};

class Dog : public Animal
{
public:
    Dog(std::string_view name) : Animal{ name, "Woof" } {}
    std::string_view speak() const { return "Woof"; }
};

void p3()
{
    const Cat cat{ "Fred" };
    std::cout << "cat is named " << cat.getName() << ", and it says " << cat.speak() << '\n';

    const Dog dog{ "Garbo" };
    std::cout << "dog is named " << dog.getName() << ", and it says " << dog.speak() << '\n';

    const Animal* pAnimal{ &cat };
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';

    pAnimal = &dog;
    std::cout << "pAnimal is named " << pAnimal->getName() << ", and it says " << pAnimal->speak() << '\n';
}

void p4()
{
    const Cat fred{ "Fred" };
    const Cat misty{ "Misty" };
    const Cat zeke{ "Zeke" };

    const Dog garbo{ "Garbo" };
    const Dog pooky{ "Pooky" };
    const Dog truffle{ "Truffle" };

    // Set up an array of pointers to animals, and set those pointers to our Cat and Dog objects
    // Note: to_array requires C++20 support (and at the time of writing, Visual Studio 2022 still doesn't support it correctly)
    const auto animals{ std::to_array<const Animal*>({&fred, &garbo, &misty, &pooky, &truffle, &zeke }) };

    // Before C++20, with the array size being explicitly specified
    // const std::array<const Animal*, 6> animals{ &fred, &garbo, &misty, &pooky, &truffle, &zeke };

    for (const auto animal : animals)
    {
        std::cout << animal->getName() << " says " << animal->speak() << '\n';
    }
}

int main()
{
    p1();
    std::cout << '\n';
    p2();
    std::cout << '\n';

    p3();
    std::cout << '\n';

    p4();
    std::cout << '\n';

    return 0;
}
