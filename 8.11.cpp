#include <iostream>

void print(int x)
{
    std::cout << x << " :int\n";
}

void print(double x)
{
    std::cout << x << " :double\n";
}

void print(std::string x)
{
    std::cout << x << " :string\n";
}

int main()
{
    print('a');
    print(true);
    print(4.5f);

    print('a');

    return 0;
}
