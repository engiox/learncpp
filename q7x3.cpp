#include <iostream>
#include <random>

void gameIntro()
{
    std::cout << "Let's play a game. I'm thinking of a number between 1 and 100.\n"
        "You have 7 tries to guess what it is.\n";
}

namespace Random
{
    std::random_device rd;
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt{ ss };
    std::uniform_int_distribution<> answerRange{ 1, 100 };

    int getRandom()
    {
        return answerRange(Random::mt);
    }
}

bool mainGame(int answer)
{
    int guess{};
    for (int chance{ 0 }; chance < 7; ++chance) {
        std::cout << "Guess #" << chance << ": ";
        std::cin >> guess;
        if (guess == answer) {
            std::cout << "Correct! You Win!\n";
            return true;
        }
        if (guess > answer) {
            std::cout << "Your guess is too high.\n";
            continue;
        }
        std::cout << "Your guess is too low.\n";
    }
    std::cout << "Sorry, you lose. The correct number was " << answer << ".\n";
    return false;
}

bool continueGameQ()
{
    while (true) {
        std::cout << "Would you like to play again (y/n) ? ";
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
    while (true) {
        gameIntro();
        int answer { Random::getRandom() };

        mainGame(answer);
        if (!continueGameQ())
            return 0;
    }

    return 0;
}
