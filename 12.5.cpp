#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    std::cout << "There " << (argc > 1 ? "are " : "is " ) << argc
              << " argument" << (argc > 1 ? "s:" : ":") << '\n';

    std::stringstream buff{};
    int val{};

    for (int idx = 0; idx < argc; ++idx) {
        buff = std::stringstream(argv[idx]);
        if (!(buff >> val)) {
            std::cout << "string: " << buff.str() << '\n';
        }
        else {
            std::cout << val << " / 2 = " << val/2 << '\n';
        }
    }

    return 0;
}
