#include <iostream>
#include <string>
#include <string_view>

template <typename T>
class Pair1
{
    T m_val1{}, m_val2{};

public:
    Pair1(T v1, T v2) : m_val1{ v1 }, m_val2{ v2 } {}
    T& first() { return m_val1; }
    T& second() { return m_val2; }
    const T& first() const { return m_val1; }
    const T& second() const { return m_val2; }
};

void p1()
{
	Pair1<int> p1 { 5, 8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair1<double> p2 { 2.3, 4.5 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}

template <typename T1, typename T2>
class Pair
{
    T1 m_val1{};
    T2 m_val2{};
 
public:
    Pair(T1 val1, T2 val2) : m_val1{ val1 }, m_val2{ val2 } {}
    T1& first() { return m_val1; }
    T2& second() { return m_val2; }
    const T1& first() const { return m_val1; }
    const T2& second() const { return m_val2; }
};

void p2()
{
	Pair<int, double> p1 { 5, 6.7 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

	const Pair<double, int> p2 { 2.3, 4 };
	std::cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
}

template <typename T>
class StringValuePair : public Pair<std::string, T>
{
public:
    StringValuePair(const std::string_view val1, const T& val2)
        : Pair<std::string, T>{ static_cast<std::string>(val1), val2 } {}
};

void p3()
{
	StringValuePair<int> svp { "Hello", 5 };
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}

int main()
{
    p1();
    std::cout << std::endl;

    p2();
    std::cout << std::endl;

    p3();
    std::cout << std::endl;

	return 0;
}
