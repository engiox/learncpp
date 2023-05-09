#include <iostream>

template <typename T>
class Auto_ptr1
{
    T* m_ptr;
public:
    Auto_ptr1(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr1() { delete m_ptr; }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
    void sayHi() { std::cout << "Hi!\n"; }
};

void someFunction()
{
    Auto_ptr1<Resource> ptr{ new Resource };

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        return;

    ptr->sayHi();
}

void passByValue(Auto_ptr1<Resource> res)
{
    std::cout << "passByValue() executed @ " << &res << '\n';
}

template <typename T>
class Auto_ptr2
{
    T* m_ptr;
public:
    Auto_ptr2(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr2() { delete m_ptr; }
    Auto_ptr2(Auto_ptr2& a) {
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
    }
    Auto_ptr2& operator=(Auto_ptr2& a) {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

int main()
{
	Auto_ptr2<Resource> res1(new Resource());
	Auto_ptr2<Resource> res2; // Start as nullptr

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	res2 = res1; // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

    return 0;
}
