#include <ios>
#include <iostream>
#include <random>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getInteger()
{
    while (true) {
        int input{};
        std::cin >> input;

        if (!std::cin) {
            std::cin.clear();
            ignoreLine();
            std::cerr << "Wrong input. Integer required.\n";
        } else {
            ignoreLine();
            return input;
        }
    }
}

bool playGame(int guess, int number)
{
    return false;
}

bool playAgain()
{
    return false;
}

int main()
{
    return 0;
}
