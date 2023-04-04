#include <iostream>
#include <iomanip>
#include <cassert>

class Tile
{
    int m_num{};
public:
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

int main()
{
    Tile tile1{ 10 };
    Tile tile2{ 8 };
    Tile tile3{ 0 }; // the missing tile
    Tile tile4{ 1 };

    std::cout << "0123456789ABCDEF\n"; // to make it easy to see how many spaces are in the next line
    std::cout << tile1 << tile2 << tile3 << tile4 << '\n';

    std::cout << std::boolalpha << tile1.isEmpty() << ' ' << tile3.isEmpty() << '\n';
    std::cout << "Tile 2 has number: " << tile2.getNum() << "\nTile 4 has number: " << tile4.getNum() << '\n';

    return 0;
}
