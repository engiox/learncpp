#include <iostream>
#include <string_view>

class Base
{
    void* c;
public:
    Base(void* vp = reinterpret_cast<void*>(0x10000000abcdefab)) : c{ vp } {};
    virtual void function1() {};
    virtual void function2() {};
};

class D1 : public Base
{
public:
    D1(void* vp = reinterpret_cast<void*>(0x10000000abcdefab)) : Base{ vp } {};
    void function1() override {};
};

class D2 : public Base
{
public:
    D2(void* vp = reinterpret_cast<void*>(0x10000000abcdefab)) : Base{ vp } {};
    void function2() override {};
};

int main()
{
    Base b{};
    D1 d1{ reinterpret_cast<void*>(0xabcdef01) };
    D2 d2{ reinterpret_cast<void*>(0xabcdef02) };

    std::cout << "sizeof(Ba) : " << sizeof(b) << " @ " << reinterpret_cast<void*>(&b) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int64_t*>(&b)) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int64_t*>(&b)+1) << '\n';
//    std::cout << std::uppercase << std::hex << uintptr_t(&b) << '\n';
    std::cout << "sizeof(D1) : " << sizeof(d1) << " @ " << reinterpret_cast<void*>(&d1) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int64_t*>(&d1)) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int64_t*>(&d1)+1) << '\n';
    std::cout << "sizeof(D2) : " << sizeof(d2) << " @ " << reinterpret_cast<void*>(&d2) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int64_t*>(&d2)) << '\n';
    std::cout << std::hex << *(reinterpret_cast<int64_t*>(&d2)+1) << '\n';

    return 0;
}
