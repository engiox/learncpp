#include <iostream>

class A
{
public:
    void print()
    {
        std::cout << "print A; ";
    }
    virtual void vprint()
    {
        std::cout << "vprint A; ";
    }
};
class B : public A
{
public:
    void print()
    {
        std::cout << "print B; ";
    }
    void vprint() override
    {
        std::cout << "vprint B; ";
    }
};


class C
{
private:
    A m_a{};

public:
    virtual A& get()
    {
        std::cout << "get A; ";
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
        std::cout << "get B; ";
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

    // case 4
    C& refs{ c };
    refs.get().print();
    refs.get().vprint();
    std::cout << '\n';

    return 0;
}
