#include <iostream>

class A
{
public:
    void print()
    {
        std::cout << "A";
    }
    virtual void vprint()
    {
        std::cout << "A";
    }
};
class B : public A
{
public:
    void print()
    {
        std::cout << "B";
    }
    void vprint() override
    {
        std::cout << "B";
    }
};


class C
{
private:
    A m_a{};

public:
    virtual A& get()
    {
        return m_a;
    }
};

class D : public C
{
private:
    B m_b{};

public:
    B& get() override
    {
        return m_b;
    }
};

int main()
{
    // case 1
    D d {};
    d.get().print();
    d.get().vprint();
    std::cout << '\n';

    // case 2
    C c {};
    c.get().print();
    c.get().vprint();
    std::cout << '\n';

    // case 3
    C& ref{ d };
    ref.get().print();
    ref.get().vprint();
    std::cout << '\n';

    return 0;
}
