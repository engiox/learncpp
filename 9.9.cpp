#include <iostream>
#include <string>
#include <cassert>
//#include <typeinfo>

void printByValue(std::string val)
{
    std::cout << val << '\n';
}

void printByReference(const std::string& ref)
{
    std::cout << ref << '\n';
}

void print(int x)
{
    std::cout << "print(int): " << x << '\n';
}

void print(int* ptr)
{
    std::cout << "print(int*): " << ( ptr ? "non-null\n" : "null\n" ) ;
}

void printByAddress(const std::string* ptr)
{
    assert(ptr);                        // DEBUG Mode
                                        
    if (!ptr) {                         //
        std::cerr << "Fatal Error!\n";  // RELEASE Mode
        return;                         //
    }                                   //
    std::cout << *ptr << '\n';
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str);
    printByReference(str);
    printByAddress(&str);

    std::cout << "type of NULL : " << typeid(NULL).name() << '\n';

    int x{ 5 };
    int* ptr{ &x };

    print(ptr);
    print(0);
//    print(NULL);      // AMBIGUOUS overloaded function resolution
    print(nullptr);

    return 0;
}
