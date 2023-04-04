#include <iostream>
#include <array>
#include <iomanip>
#include <cassert>

// Increase amount of new lines if your board isn't
// at the very bottom of the console
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

// Your code goes here

int main()
{
    Board board{};
    std::cout << board;

    return 0;
}
