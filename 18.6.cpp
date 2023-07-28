#include <iostream>

//std::ostream& operator<<(std::ostream& os, void (*fp)())
//{
//    os << std::hex << reinterpret_cast<uint64_t>(fp);
//    return os;
//}

class Base
{
    int64_t m_i {};
public:
    Base(int64_t ival = 0x1000000000000000) : m_i{ ival } {};
    virtual void function1() {};
    virtual void function2() {};
};

class D1: public Base
{
public:
    D1(int64_t ival = 0x1000000000000001) : Base{ival} {};
    void function1() override {};
};

class D2: public Base
{
public:
    D2(int64_t ival = 0x1000000000000002) : Base(ival) {};
    void function2() override {};
};

int main()
{
    Base b1 {};
    D1 d1 {3};
    D2 d2 {6};
    Base *dPtr{ &d1 };
    dPtr->function1();

    Base* dPtrA[3] = { &b1, &d1, &d2 };

    std::cout << std::dec << sizeof(b1) << ' ' << sizeof(d1) << ' ' << sizeof(d2) << '\n';

    std::cout << "sizeof(b1) : " << std::dec << sizeof(b1) << " : ";
    std::cout << "[ " << std::hex
        << *( reinterpret_cast<uint64_t*>(&b1) ) << " @ " << reinterpret_cast<uint64_t*>(&b1) << ", "
        << *( (reinterpret_cast<uint64_t*>(&b1))+1 ) << " @ " << reinterpret_cast<uint64_t*>(&b1)+1
        << " ]\n";

    std::cout << "sizeof(d1) : " << std::dec << sizeof(d1) << " : ";
    std::cout << "[ " << std::hex
        << *( reinterpret_cast<uint64_t*>(&d1) ) << " @ " << reinterpret_cast<uint64_t*>(&d1) << ", "
        << *( (reinterpret_cast<uint64_t*>(&d1))+1 ) << " @ " << reinterpret_cast<uint64_t*>(&d1)+1
        << " ]\n";

    std::cout << "sizeof(d2) : " << std::dec << sizeof(d2) << " : ";
    std::cout << "[ " << std::hex
        << *( reinterpret_cast<uint64_t*>(&d2) ) << " @ " << reinterpret_cast<uint64_t*>(&d2) << ", "
        << *( (reinterpret_cast<uint64_t*>(&d2))+1 ) << " @ " << reinterpret_cast<uint64_t*>(&d2)+1
        << " ]\n";

    for (int i{0}; i < 3; ++i) {
        uint64_t* ptmp{ (uint64_t*)*(reinterpret_cast<uint64_t*>(dPtrA[i])) };
        std::cout << "vPtrA[" << std::dec << i << "]: [ " << std::hex
            << reinterpret_cast<uint64_t>(*ptmp) << " @ " << ptmp << ", "
            << reinterpret_cast<uint64_t>(*(ptmp + 1)) << " @ " << ptmp + 1
            << " ]\n";
    }
    std::cout << '\n';

    for (int i{0}; i < 3; ++i) {
        uint64_t* ptmp{ *(reinterpret_cast<uint64_t**>(dPtrA[i])) };
        std::cout << "vPtrA[" << std::dec << i << "]: [ " << std::hex
            << *ptmp << " @ " << ptmp << ", "
            << *(ptmp + 1) << " @ " << ptmp + 1
            << " ]\n";
    }
    std::cout << '\n';

    return 0;
}
