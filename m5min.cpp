#include <exception>
#include <iostream>
#include <utility>
#include <stdexcept>

class MoveClass
{
    int* m_resource{};
public:
    MoveClass() = default;
    MoveClass(int resource)
        : m_resource{ new int{resource} } {
        std::cout << "MoveClass constructor called with value: " << resource << '\n';
    }
    MoveClass(const MoveClass& mc) {
        std::cout << "MoveClass copy constructor called\n";
        if (mc.m_resource != nullptr) {
            m_resource = new int{*mc.m_resource};
        }
    }
    MoveClass(MoveClass&& mc) noexcept
        : m_resource{ mc.m_resource } {
        std::cout << "MoveClass move constructor called\n";
        mc.m_resource = nullptr;
    }
    ~MoveClass() {
        std::cout << "MoveClass destroying " << *this << '\n';
        delete m_resource;
    }
    friend std::ostream& operator<<(std::ostream& os, const MoveClass& mc) {
        os << "MoveClass(";
        if (mc.m_resource == nullptr) {
            os << "empty";
        }
        else {
            os << *mc.m_resource;
        }
        os << ')';
        return os;
    }
};

class CopyClass
{
public:
    bool m_throw{};
    CopyClass() = default;
    CopyClass(const CopyClass& cc) : m_throw{ cc.m_throw } {
        std::cout << "CopyClass copy constructor called\n";
        if (m_throw) {
            throw std::runtime_error{ "abort!" };
        }
    }
    ~CopyClass() {
        std::cout << "CopyClass destructor called\n";
    }
};

int main()
{
    std::pair my_pair{ MoveClass{ 13 }, CopyClass{} };
    std::cout << "my_pair.first: " << my_pair.first << '\n';

    try
    {
        my_pair.second.m_throw = true;
//        std::pair moved_pair{ std::move(my_pair) };
        std::pair moved_pair{ std::move_if_noexcept(my_pair) };
        std::cout << "moved pair exists\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Error found: " << ex.what() << '\n';
    }

    std::cout << "my_pair.first: " << my_pair.first << '\n';

    return 0;
}
