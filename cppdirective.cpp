#include <iostream>

int main()
{
#ifdef DEBUG
    std::cout << "DEBUG defined" << '\n';
#endif
}
