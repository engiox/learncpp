#include <iostream>
#include <string_view>

class Base
{
    void* c{reinterpret_cast<void*>(0xabcdefab)};
public:
    virtual void function1() {};
    virtual void function2() {};
};

class D1 : public Base
{
public:
    void function1() override {};
};

class D2 : public Base
{
    void function2() override {};
};

int main()
{
    Base b{};
    D1 d1{};
    D2 d2{};

    std::cout << "sizeof(Ba) : " << sizeof(b) << " @ " << reinterpret_cast<void*>(&b) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int*>(&b)) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int*>(&b)+2) << '\n';
//    std::cout << std::uppercase << std::hex << uintptr_t(&b) << '\n';
    std::cout << "sizeof(D1) : " << sizeof(d1) << " @ " << reinterpret_cast<void*>(&d1) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int*>(&d1)) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int*>(&d1)+2) << '\n';
    std::cout << "sizeof(D2) : " << sizeof(d2) << " @ " << reinterpret_cast<void*>(&d2) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int*>(&d2)) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int*>(&d2)+2) << '\n';

    return 0;
}
