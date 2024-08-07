#include <iostream>

class Something
{
    static int s_idGenerator;
    int m_id{};

public:
    Something(): m_id{ s_idGenerator++ } {}
    int getID() const { return m_id; }
};

int Something::s_idGenerator{ 0 };

int main()
{
    Something first;
    Something second;
    Something third;

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';

    return 0;
}
