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
    os << std::hex << reinterpret_cast<std::int64_t>(fp) << ' ';
    os << std::hex << std::uppercase << reinterpret_cast<std::uint64_t>(fp);
    return os;
}

int main()
{
    fn();
    void (*fp)() { fn };
    std::cout << "fp = " << fp << '\n';

    uint64_t iarr[3];
    std::cout << &iarr[0] << " " << &iarr[1] << '\n';

    return 0;
}
