#include <iostream>

int main()
{
    unsigned short cu {65535};

    short cs { static_cast<short>(cu) };

    std::cout << cs;
    return 0;
}
