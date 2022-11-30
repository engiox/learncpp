#include <iostream>

extern int g_x;     // without extern, "duplicate symbol" link error!
//extern const int g_y;
extern int g_y;

int main()
{
    std::cout << "g_x: " << g_x << '\n';
    std::cout << "g_y: " << g_y << '\n';
    std::cout << "++g_y: " << ++g_y << '\n';

    return 0;
}
