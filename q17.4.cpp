#include <iostream>
#include <string>
#include <string_view>

class Fruit
{
    std::string m_name{};
    std::string m_color{};

public:
    Fruit(const std::string_view name, const std::string_view color)
        : m_name{ name }, m_color{ color } {}
    const std::string& getName() const { return m_name; }
    const std::string& getColor() const { return m_color; }
};

class Apple : public Fruit
{
    double m_fiber{};

public:
    Apple(const std::string_view name, const std::string_view color, double fiber)
        : Fruit(name, color), m_fiber{ fiber } {}
    double getFiber() const { return m_fiber; }
};

std::ostream& operator<<(std::ostream& out, const Apple& app)
{
    out << "Apple(" << app.getName() << ", " << app.getColor()
        << ", " << app.getFiber() << ')';
    return out;
}

class Banana : public Fruit
{
public:
    Banana(const std::string_view name, const std::string_view color)
        : Fruit(name, color) {}
};

std::ostream& operator<<(std::ostream& out, const Banana& ban)
{
    out << "Banana(" << ban.getName() << ", " << ban.getColor() << ')';
    return out;
}

int main()
{
    const Apple a{ "Red delicious", "red", 4.2 };
    std::cout << a << '\n';

    const Banana b{ "Cavendish", "yellow" };
    std::cout << b << '\n';

    return 0;
}
