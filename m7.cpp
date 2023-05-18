#include <iostream>
#include <memory>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    Resource* res { new Resource };
    std::shared_ptr<Resource> ptr1{ res };
    {
        std::shared_ptr<Resource> ptr2{ ptr1 };
//        std::shared_ptr<Resource> ptr3{ res };    // error(double free)
            // shared_ptr을 만들땐 기존 shared_ptr copy

        std::cout << "Killing two shared pointers\n";
    }
    std::cout << "Killing final shared pointer\n";

    return 0;
}
