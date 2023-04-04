#include <iostream>
#include <array>
#include <iomanip>
#include <cassert>
#include <numeric>
#include "Random.h"

constexpr int g_consoleLines{ 25 };

class Tile
{
    int m_num{};
public:
    Tile() = default;
    explicit Tile(int num) : m_num{ num }
    {
        assert( m_num >= 0 && m_num <= 15 && "Tile number out of range\n");
    }

    bool isEmpty() const
    {
        return (m_num == 0);
    }

    int getNum() const
    {
        return m_num;
    }

    void setNum(int num)
    {
        m_num = num;
    }

    friend std::ostream& operator<<(std::ostream& out, const Tile& tile)
    {
        out << ' ';
        if (tile.isEmpty()) {
            out << "   ";
        } else {
            out << std::setw(2) << tile.getNum() << ' ';
        }
        return out;
    }
};

class Board
{
    constexpr static int m_gridSize{ 4 };
    std::array<Tile, m_gridSize * m_gridSize> tiles{};
public:
    Board()
    {
        for (size_t i{0}; i < tiles.size(); ++i) {
            tiles[i].setNum( (i + 1) % 16 );
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const Board& board)
    {
        for (int i{0}; i < g_consoleLines; ++i)
            std::cout << '\n';

        for (size_t i{0}; i < board.tiles.size(); ++i) {
            std::cout << board.tiles.at(i);
            std::cout << ((i + 1)%4 ? "" : "\n");
        }
        return out;
    }
};

class Direction
{
public:
    enum Type { up, down, left, right, max_directions };
private:
    Type m_direction{};

public:
    Direction(Type dir) : m_direction{ dir } {}
    Type operator-(Type& dir)
    {
        switch (dir) {
            case up:    return down;
            case down:  return up;
            case left:  return right;
            case right: return left;
            case max_directions: return dir;
        }
    }
    friend std::ostream& operator<<(std::ostream& out, const Direction& dir)
    {
        switch (dir.m_direction) {
            case left:  std::cout << "left"; break;
            case right: std::cout << "right"; break;
            case up:    std::cout << "up"; break;
            case down:  std::cout << "down"; break;
            default:   std::cout << "oops"; break;
        }
        return out;
    }
    static Direction getRandomDirection()
    {
//        Type dir{ static_cast<Type>(Random::get(0, 3)) };
//        std::cout << "Generating random direction... " << dir << '\n';
//        return dir;
        return static_cast<Type>(Random::get(0, 3));
    }
};

namespace UserInput
{
    char getCommandFromUser()
    {
        char input{};
        while (true) {
            std::cin >> input;
            switch(input) {
                case 'w':
                case 'a':
                case 's':
                case 'd':
                case 'q':
                    std::cout << "Valid command: " << input << '\n';
//                    if (input == 'q') {
//                        std::cout << "\n\nBye!\n\n";
//                    }
                    return input;
                default:
                    continue;
            }
        }
        return input;
    }
    Direction::Type getDirection(char dir)
    {
        switch (dir) {
            case 'w': return Direction::Type::up;
            case 'a': return Direction::Type::left;
            case 's': return Direction::Type::down;
            case 'd': return Direction::Type::right;
            default:  return Direction::Type::max_directions;
        }
    }
}

int main()
{
    Board board{};
    std::cout << board;

    for (int i{0}; i < 4; ++i) {
        std::cout << "Generating random direction... ";
        std::cout << Direction::getRandomDirection() << '\n';
    }
    while (true) {
        char input{ UserInput::getCommandFromUser() };
        if (input == 'q') {
            std::cout << "\n\nBye!\n\n";
            break;
        }
    }
    return 0;
}
