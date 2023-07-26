#include <iostream>
#include <ostream>
#include <string_view>

void fn()
{
    void (*fp)() { fn };
    std::cout << "fp = " << fp << '\n';
}

std::ostream& operator<<(std::ostream& os, void (*fp)())
{
    os << std::hex << reinterpret_cast<unsigned long>(fp);
    return os;
}

int main()
{
    fn();
    void (*fp)() { fn };
    std::cout << "fp = " << fp << '\n';
}
