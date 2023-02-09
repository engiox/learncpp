#include <iostream>
#include <string>

int main()
{
    std::string str { "I saw a red car yesterday" };

    str.erase(8, 3);
    str.insert(8, "green");
    std::cout << str << '\n';

    str.replace(8, 5, "blue");
    std::cout << str << '\n';

    return 0;
}
