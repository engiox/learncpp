#include <cassert>
#include <ctime>
#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>
#include <random>

enum class CardRank {
    rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10,
    rank_jack, rank_queeen, rank_king, rank_ace, max_ranks
};

enum class CardSuit {
    clubs, diamonds, hearts, spades, max_suits
};

struct Card
{
    CardRank rank{};
    CardSuit suit{};
};

void printCard(const Card &card)
{
    char ra{}, su{};

    switch (card.rank) {
        case CardRank::rank_2:       ra = '2'; break;
        case CardRank::rank_3:       ra = '3'; break;
        case CardRank::rank_4:       ra = '4'; break;
        case CardRank::rank_5:       ra = '5'; break;
        case CardRank::rank_6:       ra = '6'; break;
        case CardRank::rank_7:       ra = '7'; break;
        case CardRank::rank_8:       ra = '8'; break;
        case CardRank::rank_9:       ra = '9'; break;
        case CardRank::rank_10:      ra = 'T'; break;
        case CardRank::rank_jack:    ra = 'J'; break;
        case CardRank::rank_queeen:  ra = 'Q'; break;
        case CardRank::rank_king:    ra = 'K'; break;
        case CardRank::rank_ace:     ra = 'A'; break;
        default: ra = '?'; break;
    }

    switch (card.suit) {
        case CardSuit::clubs:        su = 'C'; break;
        case CardSuit::diamonds:     su = 'D'; break;
        case CardSuit::hearts:       su = 'H'; break;
        case CardSuit::spades:       su = 'S'; break;
        default: su = '?'; break;
    }

    std::cout << ra << su;
}

std::array<Card, 52> createDeck()
{
    std::array<Card, 52> deck{};
//    size_t idx{0};

    for (size_t iSuit{0}; iSuit < static_cast<int>(CardSuit::max_suits); ++iSuit) {
        for (size_t iRank{0}; iRank < static_cast<int>(CardRank::max_ranks); ++iRank) {
            deck[iSuit*13 + iRank].suit = static_cast<CardSuit>(iSuit);
            deck[iSuit*13 + iRank].rank = static_cast<CardRank>(iRank);
//            deck[idx].suit = static_cast<CardSuit>(iSuit);
//            deck[idx].rank = static_cast<CardRank>(iRank);
//            ++idx;
        }
    }

    return deck;
}

void printDeck(const std::array<Card, 52> &deck)
{
    for (int i = 0;const auto &card : deck) {
        printCard(card);
        std::cout << (++i % 13 ? ' ' : '\n');
    }
    std::cout << '\n';
}

void shuffleDeck(std::array<Card, 52> &deck)
{
    std::mt19937 mt{static_cast<std::mt19937::result_type>(std::time(nullptr))};
    std::shuffle(deck.begin(), deck.end(), mt);
}

int getCardValue(const Card &cd)
{
    switch (cd.rank) {
        case CardRank::rank_2:      return 2;
        case CardRank::rank_3:      return 3;
        case CardRank::rank_4:      return 4;
        case CardRank::rank_5:      return 5;
        case CardRank::rank_6:      return 6;
        case CardRank::rank_7:      return 7;
        case CardRank::rank_8:      return 8;
        case CardRank::rank_9:      return 9;
        case CardRank::rank_10:
        case CardRank::rank_jack:
        case CardRank::rank_queeen:
        case CardRank::rank_king:   return 10;
        case CardRank::rank_ace:    return 11;
        default:
            assert(false && "should never happen");
            return 0;
    }
}

bool playBlackjack(const std::array<Card, 52> &deck)
{
    int dealerScore{0}, playerScore{0};
    unsigned index{0};

    std::cout << "Player got: "; printCard(deck[0]);
    std::cout << ", "; printCard(deck[1]); std::cout << '\n';
    playerScore += getCardValue(deck[0]) + getCardValue(deck[1]);
    if (playerScore > 21) playerScore -= 10;
//    std::cout << "... Score: " << getCardValue(deck[0]) +
//                                  getCardValue(deck[1]) << '\n';

    std::cout << "Dealer got: "; printCard(deck[2]);
    std::cout << ", **"; printCard(deck[3]); std::cout << '\n';
//    std::cout << "... Score: " << getCardValue(deck[2]) << '\n';

    index = 4;

    while (true) {
        std::cout << "Player score: " << playerScore << '\n';
        if (playerScore > 21) {
            std::cout << "Dealer win!\n";
            return false;
        }
        std::cout << "... Hit or Stand? (H or S)\n";
        char ans{};
        std::cin >> ans;

        if (ans == 'S')
            break;
        else if (ans == 'H') {
            std::cout << "Player got: "; printCard(deck[index]); std::cout << '\n';
            if (getCardValue(deck[index]) == 11 && (playerScore >= 11))
                playerScore += 1;
            else {
                playerScore += getCardValue(deck[index]);
                ++index;
                continue;
            }
        } else {
            std::cout << "Try Again!\n";
            continue;
        }
    }

    std::cout << "Dealer got: "; printCard(deck[2]);
    std::cout << ", "; printCard(deck[3]); std::cout << '\n';
    dealerScore += getCardValue(deck[2]) + getCardValue(deck[3]);
    if (dealerScore > 21) dealerScore -= 10;

    while (true) {
        std::cout << "Dealer score: " << dealerScore << '\n';
        if ((dealerScore > 21) ||
            (dealerScore >= 17 && dealerScore < playerScore)) {
            std::cout << "Player win!\n";
            return true;
        }
        if (dealerScore >= 17 || (dealerScore > playerScore)) {
            std::cout << "Dealer win!\n";
            return false;
        }
        std::cout << "Dealer got: "; printCard(deck[index]); std::cout << '\n';
        if (getCardValue(deck[index]) == 11 && (dealerScore >= 11))
            dealerScore += 1;
        else {
            dealerScore += getCardValue(deck[index]);
            ++index;
            continue;
        }
    }

    return true;
}

int main()
{
    auto deck{createDeck()};

    printDeck(deck);
    shuffleDeck(deck);
    printDeck(deck);

    playBlackjack(deck);

    return 0;
}
