#include <iostream>

class Accumulator
{
    int m_value{0};
public:
    Accumulator(int val) : m_value{val} {}
    void print() { std::cout << "Accumulator: " << m_value << '\n'; }
    void add(int val) { m_value += val; }
    void reset() { m_value = 0; }
    friend void reset(Accumulator &accum);
    friend bool isEqual(const Accumulator &val1, const Accumulator &val2);
};

void reset(Accumulator &acc)
{
    acc.m_value = 0;
}

bool isEqual(const Accumulator &val1, const Accumulator &val2)
{
    return (val1.m_value == val2.m_value);
}

class Storage
{
private:
    int m_nValue {};
    double m_dValue {};
public:
    Storage(int nValue, double dValue)
       : m_nValue { nValue }, m_dValue { dValue }
    {
    }

    // Make the Display class a friend of Storage
    friend class Display;
};

class Display
{
private:
    bool m_displayIntFirst;

public:
    Display(bool displayIntFirst)
         : m_displayIntFirst { displayIntFirst }
    {
    }

    void displayItem(const Storage& storage)
    {
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        else // display double first
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }
};

int main()
{
    Storage storage{5, 6.7};
    Display display{false};

    display.displayItem(storage);

    return 0;
}
