#include <iostream>
#include <typeinfo>

int main()
{
//    {
//        int x{5};
//        std::cout << "x = " << x << '\n';
//        std::cout << "&x = " << &x << '\n';
//    }
//
//    {
//        int i{ 5 };
//        double d{ 7.0 };
//
//        int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
//        int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double
//        double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
//        double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int
//    }
//
//    {
//        int* ptr0{ 5 }; // not okay
//        int* ptr1{ 0x0012FF7C }; // not okay, 0x0012FF7C is treated as an integer literal
//    }
//
    {
        int x{ 4 };
        std::cout << typeid(&x).name() << '\n'; // print the type of &x
    }

    {
        char* chPtr{};        // chars are 1 byte
        int* iPtr{};          // ints are usually 4 bytes
        long double* ldPtr{}; // long doubles are usually 8 or 12 bytes

        std::cout << sizeof(chPtr) << '\n'; // prints 4
        std::cout << sizeof(iPtr) << '\n';  // prints 4
        std::cout << sizeof(ldPtr) << '\n'; // prints 4
    }

    {
        int x{ 5 };
        int *ptr{ &x };

        std::cout << *ptr << '\n';
        {
            int y{ 6 };
            ptr = &y;

            std::cout << *ptr << '\n';
        }
        std::cout << *ptr << '\n';
    }

    return 0;
}
