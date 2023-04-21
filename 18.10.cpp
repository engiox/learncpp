#include <iostream>
#include <string>
#include <string_view>

class Base
{
protected:
    int m_value{};

public:
    Base(int val) : m_value{ val } {}
    virtual ~Base() = default;
};

class Derived : public Base
{
protected:
    std::string m_name;

public:
    Derived(int val, std::string_view name)
        : Base{ val }, m_name{ name } {}
    const std::string& getName() { return m_name; }
};

Base* getObject(bool returnDerived)
{
    if (returnDerived)
        return new Derived{ 1, "Apple" };
    else
        return new Base{ 2 };
}

int main()
{
    Base* b;
    do {
        std::cout << "getDerived ? (y/n) : ";
        char ch;
        bool gD;
        std::cin >> ch;

        switch (ch) {
            case 'y':
            case 'Y':
                gD = true;
                break;
            default:
                gD = false;
                break;
        }
        b = getObject(gD);
        std::cout << "getDerived: " << (gD ? "true" : "false") << '\n';
        std::cout << "static_cast: " << static_cast<Derived*>(b) << '\n';
        std::cout << "dynamic_cast: " << dynamic_cast<Derived*>(b) << '\n';
        if (ch == 'q' || ch == 'Q')
            break;
    } while (true);

    delete b;

    return 0;
}
