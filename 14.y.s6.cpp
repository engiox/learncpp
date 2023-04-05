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
        return static_cast<Type>(Random::get(0, 3));
    }
};

struct Point
{
    int m_xaxis{}, m_yaxis{};
    Point(int x = 0, int y = 0) : m_xaxis{ x }, m_yaxis{ y } {};
    friend bool operator==(const Point& p1, const Point& p2)
    {
        return (p1.m_xaxis == p2.m_xaxis) && (p1.m_yaxis == p2.m_yaxis);
    }
    friend bool operator!=(const Point& p1, const Point& p2)
    {
        return !(p1 == p2);
    }
    const Point getAdjacentPoint(const Direction::Type dir)
    {
        Point dest{m_xaxis, m_yaxis};

        switch (dir) {
            case Direction::up:
                if (m_yaxis > 0)
                    --dest.m_yaxis;
                break;
            case Direction::down:
                if (m_yaxis < 3)
                    ++dest.m_yaxis;
                break;
            case Direction::left:
                if (m_xaxis > 0)
                    --dest.m_xaxis;
                break;
            case Direction::right:
                if (m_xaxis < 3)
                    ++dest.m_xaxis;
                break;
            default: ;
        }
        return dest;
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

    std::cout << std::boolalpha;
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::up)    == Point{ 1, 0 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::down)  == Point{ 1, 2 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::left)  == Point{ 0, 1 }) << '\n';
    std::cout << (Point{ 1, 1 }.getAdjacentPoint(Direction::right) == Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 2, 1 }) << '\n';
    std::cout << (Point{ 1, 1 } != Point{ 1, 2 }) << '\n';
    std::cout << !(Point{ 1, 1 } != Point{ 1, 1 }) << '\n';

    return 0;
}
