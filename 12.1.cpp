#include <iostream>

int foo() // code starts at memory address 0x002717f0
{
    return 5;
}

int goo()
{
    return 6;
}

int foo1(int x)
{
    return x;
}

int main()
{
    std::cout << reinterpret_cast<void*>(foo) << '\n'; // we meant to call foo(), but instead we're printing foo itself!
    std::cout << reinterpret_cast<void*>(&foo) << '\n';

    int (*fPtr)();

    int (*fPtr1)(){ foo };
    std::cout << reinterpret_cast<void*>(fPtr1) << '\n';

    std::cout << reinterpret_cast<void*>(goo) << '\n';
    fPtr1 = foo;
    std::cout << reinterpret_cast<void*>(fPtr1) << '\n';

    int (*fPtr2)(){ nullptr };
    void *vptr{ reinterpret_cast<void*>(foo) };

    fPtr2 = goo;

    std::cout << fPtr1() << '\n';
    std::cout << fPtr2() << '\n';

    auto fcnPtrA{ &foo1 };
    std::cout << fcnPtrA(5) << '\n';

    return 0;
}
