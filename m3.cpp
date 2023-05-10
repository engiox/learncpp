#include <iostream>

template <typename T>
class Auto_ptr3
{
    T* m_ptr;
public:
    Auto_ptr3(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr3() { delete m_ptr; }
    Auto_ptr3(const Auto_ptr3& a) {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr3& operator=(const Auto_ptr3& a) {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr3<Resource> generateResource()
{
    Auto_ptr3<Resource> res{ new Resource };
    return res;
}

template <typename T>
class Auto_ptr4
{
    T* m_ptr;
public:
    Auto_ptr4(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr4() { delete m_ptr; }
    Auto_ptr4(const Auto_ptr4& a) {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr4(Auto_ptr4&& a) noexcept : m_ptr{ a.m_ptr } {
        a.m_ptr = nullptr;
    }
    Auto_ptr4& operator=(const Auto_ptr4& a) {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr4& operator=(Auto_ptr4&& a) noexcept {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() { return this == nullptr; }
};

Auto_ptr4<Resource> generateResourceR()
{
    Auto_ptr4<Resource> res{ new Resource };
    return res;
}

template <typename T>
class Auto_ptr5
{
    T* m_ptr;
public:
    Auto_ptr5(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr5() { delete m_ptr; }
};

int main()
{
//    Auto_ptr3<Resource> mainres;
//    mainres = generateResource();
//
//    std::cout << '\n';

    Auto_ptr4<Resource> mainresR;
    std::cout << "mainres created\n";
    mainresR = generateResourceR();
    std::cout << "mainres value assiigned by generateResource()\n";

    std::cout << "finishing\n";

    return 0;
}
