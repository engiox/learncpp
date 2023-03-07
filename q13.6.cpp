#include <iostream>

class RGBA
{
    uint8_t m_red{};
    uint8_t m_green{};
    uint8_t m_blue{};
    uint8_t m_alpha{};

    public:
        RGBA(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255)
            : m_red{ r }, m_green{ g }, m_blue{ b }, m_alpha{ a } {}
        void print() {
            std::cout << "r=" << static_cast<int>(m_red) << " g=" << static_cast<int>(m_green)
                      << " b=" << static_cast<int>(m_blue) << " a=" << static_cast<int>(m_alpha) << '\n';
        }
};

int main()
{
    RGBA teal{0, 127, 127};
    teal.print();

    return  0;
}
