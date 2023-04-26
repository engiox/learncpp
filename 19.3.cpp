#include <ios>
#include <iostream>

template <typename T>
class Storage
{
    T m_value;
public:
    Storage(const T val) : m_value{ val } {}
    ~Storage() {};      // = default won't work
    void print() const { std::cout << m_value << '\n'; }
};

template <>
void Storage<double>::print() const
{
    std::cout << std::scientific << m_value << '\n';
}

template <>
Storage<char*>::Storage(char* const value)
{
    if (!value) return;

    int length{0};
    while (value[length] != '\0')
        ++length;
    ++length;
    m_value = new char[static_cast<size_t>(length)];
    for (int count{0}; count < length; ++count) {
        m_value[count] = value[count];
    }
}

template <>
Storage<char*>::~Storage()
{
    delete[] m_value;
}

void p1()
{
    // Define some storage units
    Storage<int> nValue { 5 };
    Storage<double> dValue { 6.7 };

    // Print out some values
    nValue.print();
    dValue.print();
}

void p2()
{
    // Dynamically allocate a temporary string
    std::string s;

    // Ask user for their name
    std::cout << "Enter your name: ";
    std::cin >> s;

    // Store the name
    Storage<char*> storage(s.data());

    storage.print(); // Prints our name

    s.clear(); // clear the std::string

    storage.print(); // Prints nothing
}

int main()
{
    p1();
    p2();
}
