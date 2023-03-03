#include <iostream>

class IntPair {
    int m_int1{};
    int m_int2{};
    public:
//    IntPair();
//    IntPair(int a1, int a2);
    IntPair() { m_int1 = 0; m_int2 = 0; }
    IntPair(int a1, int a2) { m_int1 = a1, m_int2 = a2; }
    void set(int p1, int p2) {
        m_int1 = p1;
        m_int2 = p2;
    }
    void print() {
        std::cout << "Pair(" << m_int1 << ", " << m_int2 << ")\n";
    }
};

int main()
{
    IntPair p1;
    p1.set(1, 1);

    IntPair p2{ 2, 2 };

    p1.print();
    p2.print();

    return 0;
}
