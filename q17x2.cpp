#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

class Fruit
{
protected:
    std::string m_name{};
    std::string m_color{};
public:
    Fruit(std::string_view name, std::string_view color) : m_name{ name }, m_color{ color } {}
};

class Apple : public Fruit
{
public:
    Apple(std::string_view color = "red", std::string_view name = "apple")
        : Fruit(name, color) {}
    const std::string& getName() { return m_name; }
    const std::string& getColor() { return m_color; }
};

class Banana : public Fruit
{
public:
    Banana(std::string_view color = "yellow", std::string_view name = "banana")
        : Fruit(name, color) {}
    const std::string& getName() { return m_name; }
    const std::string& getColor() { return m_color; }
};

class GrannySmith : public Apple
{
public:
    GrannySmith(std::string_view color = "green", std::string_view name = "granny smith")
        : Apple(color, name) {}
    const std::string& getName() { return m_name; }
    const std::string& getColor() { return m_color; }
};

int main()
{
	Apple a{ "red" };
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

	return 0;
}
