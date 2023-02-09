#include <iostream>
#include <iomanip>
#include <string>

const std::string& getConstRef()
{
    static std::string hello{ "Hello, World!\n" };

    std::cout << std::setw(16) <<  "hello @ " << &hello << '\n';

    return hello;
}

std::string& getRef()
{
    static std::string bye{ "Bye, World\n" };

    std::cout << std::setw(16) << "bye @ " << &bye << '\n';

    return bye;
}

std::string* getPtr()
{
    static std::string strName{ "getPtr()" };
    return &strName;
}

const std::string* getConstPtr()
{
    const static std::string strName{ "getConstStr()" };
    return &strName;
}


int main()
{
    {
        auto h1{ getConstRef() };
        std::cout << std::setw(16) << "auto @ " << &h1 << '\n';
        h1.append("");

        const auto h2{ getConstRef() };
        std::cout << std::setw(16) << "const auto @ " << &h2 << '\n';
        //    h2.append("");    // can't modify CONST (top-level)

        auto& h3{ getConstRef() };
        std::cout << std::setw(16) << "auto& @ " << &h3 << '\n';
        //    h3.append("");    // can't modify CONST (low-level, UNDERLYING OBJECT)

        const auto& h4{ getConstRef() };
        std::cout << std::setw(16) << "const auto& @ " << &h4 << '\n';
        //    h4.append("");    // can't modify CONST (top(redundant)- & low-level)
    }

    {
        auto b1{ getRef() };
        std::cout << std::setw(16) << "auto @ " << &b1 << '\n';
        b1.append("");

        const auto b2{ getRef() };
        std::cout << std::setw(16) << "const auto @ " << &b2 << '\n';
        //    b2.append("");

        auto& b3{ getRef() };
        std::cout << std::setw(16) << "auto& @ " << &b3 << '\n';
        b3.append("");

        const auto& b4{ getRef() };
        std::cout << std::setw(16) << "const auto& @ " << &b4 << '\n';
        //    b4.append("");
    }

    {
        auto ptr1{ getPtr() };
        std::cout << std::setw(16) << "auto ptr @ " << ptr1 << '\n';

        auto* ptr2{ getPtr() };
        std::cout << std::setw(16) << "auto* ptr @ " << ptr2 << '\n';

        auto ptr3{ *getPtr() };
        std::cout << std::setw(16) << "auto *getPtr() @ " << ptr3 << '\n';

//        auto* ptr4{ *getPtr() };
//        std::cout << std::setw(16) << "auto* *getPtr() @ " << ptr4 << '\n';
    }

    // Type deduction and const pointers (optional reading)
    {
        const auto ptr1{ getPtr() };
        *ptr1 = "testing...\n";
//        ptr1 = nullptr;
        auto const ptr2{ getPtr() };
        *ptr2 = "testing...\n";
//        ptr2 = nullptr;

        const auto* ptr3{ getPtr() };
//        *ptr3 = "testing...\n";
        std::cout << *ptr3 << '\n';
        ptr3 = nullptr;
        auto* const ptr4{ getPtr() };
        *ptr4 = "testing...\n";
//        ptr4 = nullptr;
    }

    {
        auto ptr1{ getConstPtr() };  // const std::string*
        *ptr1 = "testing...\n";
        ptr1 = nullptr;
        auto* ptr2{ getConstPtr() }; // const std::string*
        *ptr2 = "testing...\n";
        ptr2 = nullptr;

        auto const ptr3{ getConstPtr() };  // const std::string* const
        *ptr3 = "testing...\n";
        ptr3 = nullptr;
        const auto ptr4{ getConstPtr() };  // const std::string* const
        *ptr4 = "testing...\n";
        ptr4 = nullptr;

        auto* const ptr5{ getConstPtr() }; // const std::string* const
        *ptr5 = "testing...\n";
        ptr5 = nullptr;
        const auto* ptr6{ getConstPtr() }; // const std::string*
        *ptr6 = "testing...\n";
        ptr6 = nullptr;

        const auto const ptr7{ getConstPtr() };  // error: const qualifer can not be applied twice
        *ptr7 = "testing...\n";
        ptr7 = nullptr;
        const auto* const ptr8{ getConstPtr() }; // const std::string* const
        *ptr8 = "testing...\n";
        ptr8 = nullptr;
    }
                                             //
    return 0;
}
