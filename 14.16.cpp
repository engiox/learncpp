#include <iostream>
#include <cstring> // for strlen()
#include <cassert> // for assert()

class MyString
{
private:
    char* m_data{};
    int m_length{};

public:
    MyString(const char* source = "" )
    {
        assert(source); // make sure source isn't a null string

        // Find the length of the string
        // Plus one character for a terminator
        m_length = std::strlen(source) + 1;

        // Allocate a buffer equal to this length
        m_data = new char[static_cast<size_t>(m_length)];

        // Copy the parameter string into our internal buffer
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    ~MyString() // destructor
    {
        // We need to deallocate our string
        delete[] m_data;
    }

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};

class XString
{
private:
    char* m_pstr{};
    size_t m_len{};
public:
    XString(const char* pstr = "") : m_pstr{ new char[ std::strlen(pstr) + 1 ] },
                                     m_len{ std::strlen(pstr) }
    {
        assert(pstr && "XString: Null pointer detected!\n");

        for (size_t i{0}; i < m_len; ++i) {
            m_pstr[i] = pstr[i];
        }
    }
    ~XString()
    {
        delete[] m_pstr;
    }
};

int main()
{
    MyString hello{ "Hello, world!" };
    {
        MyString copy{ hello };
        std::cout << copy.getString() << '\n';
    }
    std::cout << hello.getString() << '\n';

    return 0;
}
