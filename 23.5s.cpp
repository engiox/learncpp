#include <ranges>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <cctype>
#include <algorithm>
#include <map>

bool isValidName(std::string_view name)
{
    return std::ranges::all_of(name, [](char ch) {
            return (std::isalpha(ch) || std::isspace(ch));
            });
}

void p1()
{
    std::string name;

    do {
        std::cout << "Enter your name: ";
        std::getline(std::cin, name);
    } while (!isValidName(name));

    std::cout << "Hello " << name << "!\n";
}

bool inputMatches(std::string_view input, std::string_view pattern)
{
    if (input.length() != pattern.length())
        return false;

    static const std::map<char, int (*)(int)> validators {
        { '#', &std::isdigit },
        { '_', &std::isspace },
        { '@', &std::isalpha },
        { '?', [](int){ return 1; } }
    };

    return std::ranges::equal(input, pattern, [](char ch, char mask) -> bool {
        if (auto found{ validators.find(mask) }; found != validators.cend()) {
            return (*found->second)(ch);
        } else {
            return (ch == mask);
        }
        });
}

void p2()
{
    std::string phoneNumber;

    do {
        std::cout << "Enter a phone number (###) ###-####: ";
        std::getline(std::cin, phoneNumber);
    } while (!inputMatches(phoneNumber, "(###) ###-####"));

    std::cout << "You entered: " << phoneNumber << '\n';
}

int main()
{
    p1();
    p2();

    return 0;
}
