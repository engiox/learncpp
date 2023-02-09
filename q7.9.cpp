#include <iostream>

void first()
{
    for (int i{0}; i <= 20; ++i) {
        if (i%2 == 0) {
            std::cout << i << ' ';
        }
    }
}


int main()
{
    first();

    return 0;
}
