#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "There " << (argc > 1 ? "are " : "is " ) << argc
              << " argument" << (argc > 1 ? "s:" : ":") << '\n';

    for (auto count{0}; count < argc; ++count) {
        std::cout << count << ' ' << argv[count] << '\n';
    }

    if ("") std::cout << "empty string or pointer?\n";

    return 0;
}
