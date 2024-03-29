#include <iostream>

template <typename T>
class Storage
{
private:
    T m_value;
public:
    Storage(T value) : m_value { value } {}
    ~Storage() {}
    void print() const { std::cout << m_value << '\n'; }
};

template <typename T>
class Storage<T*>
{
    T* m_value{};
public:
    Storage(T* value) : m_value{ new T{ *value } } {}
    ~Storage() { delete m_value; }
    void print() const { std::cout << *m_value << '\n'; }
};

template <>
class Storage<char*>
{
    char* m_value{};
public:
    Storage(char* const szValue) {
        int strLen{0};
        while (szValue[strLen] != '\0') {
            ++strLen;
        }
        ++strLen;
        m_value = new char[strLen]{};
        for (int i{0}; i < strLen; ++i) {
            m_value[i] = szValue[i];
        }
    }
    ~Storage() { delete[] m_value; }
    void print() const { std::cout << m_value; }
};

int main()
{
	// Declare a non-pointer Storage to show it works
	Storage<int> myint { 5 };
	myint.print();

	// Declare a pointer Storage to show it works
	int x { 7 };
	Storage<int*> myintptr { &x };

	// Let's show that myintptr is separate from x.
	// If we change x, myintptr should not change
	x = 9;
	myintptr.print();

    // Dynamically allocate a temporary string
	char* name{ new char[40] { "Alex" } };

	// Store the name
	Storage<char*> myname{ name };

	// Delete the temporary string
	delete[] name;

	// Print out our name to prove we made a copy
	myname.print();

    return 0;
}
