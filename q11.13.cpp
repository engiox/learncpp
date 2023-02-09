#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view names[] { "Alex", "Betty", "Caroline", "Dave", "Emily", "Fred", "Greg", "Holly" };
    std::string buff{};
    bool found{ false };

    std::cout << "Enter a name: ";

    std::getline(std::cin >> std::ws, buff, '\n');

    for (auto &name : names) {
        if (name == buff) {
            std::cout << name << " was found.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << buff << " was not found.\n";
    }

    return 0;
}
