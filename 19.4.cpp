#include <cstdint>
#include <ios>
#include <iostream>

template <typename T>
class Storage8
{
    T m_array[8];
public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }
    const T& get(int index) const
    {
        return m_array[index];
    }
    T& operator[](const int index)
    {
        return m_array[index];
    }
};

template <>
class Storage8<bool>
{
    std::uint8_t m_data{};
public:
    void set(int index, bool value)
    {
        auto mask{ 1 << index };
        if (value)
            m_data |= mask;
        else
            m_data &= ~mask;
    }
    bool get(int index)
    {
        auto mask{ 1 << index };
        return m_data & mask;
    }
};

int main()
{
    Storage8<int> intStorage;
    for (int i{0}; i < 8; ++i)
        intStorage[i] = i;
    for (int i{0}; i < 8; ++i)
        std::cout << intStorage[i] << '\n';

    Storage8<bool> bStorage;
    for (int i{0}; i < 8; ++i)
        bStorage.set(i, i&3);
    std::cout << std::boolalpha;
    for (int i{0}; i < 8; ++i)
        std::cout << bStorage.get(i) << '\n';

    return 0;
}
