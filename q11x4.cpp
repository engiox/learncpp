#include <iostream>

int printChar(char *cstr)
{
    for (int idx{0};; ++idx) {
        if (cstr[idx] == '\0') return idx;
        std::cout << static_cast<char>(cstr[idx]);
    }
}

int printCh(char *cstr)
{
    int numCh{0};
    while (*cstr) {
        std::cout << *cstr;
        ++cstr, ++numCh;
    }
    return numCh;
}

int main()
{
    char test[]{ "Hello, world!" };

    int numChar{};

    numChar = printChar(test);
    std::cout << '\n' << numChar << " char(s) printed.\n";

    numChar = printCh(test);
    std::cout << '\n' << numChar << " char(s) printed.\n";

    return 0;
}
