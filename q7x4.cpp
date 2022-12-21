#include <ios>
#include <iostream>
#include <random>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getInteger(int numChances)
{
    while (true) {
        std::cout << "guesses #" << numChances << ": ";
        int input{};
        std::cin >> input;

        if (!std::cin || input < 1 || input > 100) {
            std::cin.clear();
            ignoreLine();
            std::cerr << "Wrong input. Integer between 1 and 100 required.\n";
        } else {
            ignoreLine();
            return input;
        }
    }
}

bool playGame(int guesses, int number)
{
    for (int numChances{ 1 }; numChances <= guesses; ++numChances) {
        int answer{ getInteger(numChances) };
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
        }
    }
}

int main()
{
    std::random_device rd;
    std::seed_seq seq{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt{ seq };
    std::uniform_int_distribution<> die{ 1, 100 };

    constexpr int numChances{ 7 };

    do {
        std::cout << "Let's play a game. I'm thinking of a number between 1 and 100.\n"
                     "You have " << numChances << " tries to guess what it is.\n";
        int numRand{ die(mt) };

        if (playGame(numChances, numRand)) {
            std::cout << "Correct! You win!\n";
        } else {
            std::cout << "Sorry, you lose. The correct number was " << numRand << '\n';
        }
    } while (playAgain());

    std::cout << "Thank you for playing.\n";

    return 0;
}
