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

bool playGame(int guesses, int number)
{
    for (int numChances{ 1 }; numChances <= guesses; ++numChances) {
        std::cout << "guesses #" << numChances << ": ";
        int answer{ getInteger() };
        if (answer > number) {
            std::cout << "Your guess is too high.\n";
        } else if (answer < number) {
            std::cout << "Your guess is too low.\n";
        } else {
            return true;
        }
    }
    return false;
}

bool playAgain()
{
    while (true) {
        std::cout << "Would you like to try again (y/n) ? ";
        char yorn{};
        std::cin >> yorn;

        switch (yorn) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                continue;
        }
    }
}

int main()
{
    return 0;
}
