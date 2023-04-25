#include <iostream>
#include <string_view>

void p1()
{
    class BaseP1
    {
    public:
        virtual void print() const { std::cout << "BaseP1"; }
        virtual ~BaseP1() = default;
    };

    class DerivedP1 : public BaseP1
    {
    public:
        void print() const override { std::cout << "DerivedP1"; }
    };

    DerivedP1 d;
    BaseP1& b{ d };

    std::cout << "b is a ";
    b.print();
    std::cout << '\n';
}

class BaseP2
{
public:
    virtual ~BaseP2() = default;
    virtual std::string_view identify() const { return "BaseP2"; }
    friend std::ostream& operator<<(std::ostream& out, const BaseP2& b)
    {
        out << b.identify();
        return out;
    }
};

class DerivedP2 : public BaseP2
{
public:
    virtual ~DerivedP2() = default;
    virtual std::string_view identify() const { return "DerivedP2"; }
};

void p2()
{
    BaseP2 b;
    std::cout << "Base: " << b << '\n';

    DerivedP2 d;
    std::cout << "Derived: " << d << '\n';

    BaseP2& bref{ d };
    std::cout << "Base_ref(Derived): " << bref << '\n';
}

class BaseP3
{
public:
    virtual ~BaseP3() = default;
    friend std::ostream& operator<<(std::ostream& out, const BaseP3& b)
    {
        return b.print(out);
    }
    virtual std::ostream& print(std::ostream& out) const
    {
        out << "Base";
        return out;
    }
};

struct Employee
{
    std::string name{};
    int id{};

    friend std::ostream& operator<<(std::ostream& out, const Employee& e)
    {
        out << "Employee(" << e.name << ", " << e.id << ')';
        return out;
    }
};

class DerivedP3 : public BaseP3
{
private:
    Employee m_e{};

public:
    DerivedP3(const Employee& e) : m_e{ e } {}
    std::ostream& print(std::ostream& out) const override
    {
        out << "Derived: ";
        out << m_e;
        return out;
    }
};

void p3()
{
    BaseP3 b;
    std::cout << "BaseP3: " << b << '\n';

    DerivedP3 d{ Employee{ "Jim", 4 } };
    std::cout << "DerivedP3: " << d << '\n';

    BaseP3& bref{ d };
    std::cout << "BaseP3_ref(d): " << bref << '\n';
}

int main()
{
    p1();
    std::cout << '\n';
    p2();
    std::cout << '\n';
    p3();

    return 0;
}
