#include <iostream>

class Something
{
    static inline int s_idGenerator{0};
    int m_id{};

public:
    Something(): m_id{ s_idGenerator++ } {}
    int getID() const { return m_id; }
    static int getSID() { return s_idGenerator; }
};

int main()
{
    std::cout << "SID: " << Something::getSID() << '\n';

    Something first;
    Something second;
    Something third;
    std::cout << "instantiated\n";
    std::cout << "SID: " << Something::getSID() << '\n';

    std::cout << "firstID: " << first.getID() << '\n';
    std::cout << "secondID: " << second.getID() << '\n';
    std::cout << "thirdID: " << third.getID() << '\n';
    std::cout << "SID: " << Something::getSID() << '\n';

    return 0;
}
