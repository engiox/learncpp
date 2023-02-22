#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    std::cout << "There " << (argc > 1 ? "are " : "is " ) << argc
              << " argument" << (argc > 1 ? "s:" : ":") << '\n';

    std::stringstream buff{ argv[1] };
    int val{};

    if (!(buff >> val))
        val = 0;

    std::cout << val << " / 2 = " << val/2 << '\n';

//    for (auto count{0}; count < argc; ++count) {
//        buff << argv[count];
//        if ((buff >> val))
//            std::cout << val << " / 2 = " << val/2 << '\n';
//        else
//            std::cout << argv[count] << '\n';
//    }

    return 0;
}
