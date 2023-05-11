#include <iostream>
#include <string>

class Name
{
private:
    std::string m_name; // std::string is move capable

public:
    Name(std::string name) : m_name{ name }
    {
    }

    Name(const Name& name) = delete;
    Name& operator=(const Name& name) = delete;

    void swap(Name& n1, Name& n2) noexcept
    {
        Name tmp{ n1.m_name };
        n1.m_name = n2.m_name;
        n2.m_name = tmp.m_name;
    }

    Name(Name&& name)
    {
        std::cout << "Move ctor\n";

        swap(*this, name); // bad!
    }

    Name& operator=(Name&& name)
    {
        std::cout << "Move assign\n";

        swap(*this, name); // bad!

        return *this;
    }

    const std::string& get() { return m_name; }
};

int main()
{
    Name n1{ "Alex" };
    n1 = Name{"Joe"}; // invokes move assignment

    std::cout << n1.get() << '\n';

    return 0;
}
