#include <iostream>
#include <string>
#include <string_view>
#include <array>

class Creature
{
protected:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_dpattack{};
    int m_gold{};

public:
    Creature(std::string_view name, char symbol, int health, int dpa, int gold)
        : m_name{ name }, m_symbol{ symbol }, m_health{ health },
          m_dpattack{ dpa }, m_gold{ gold } {}

    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDPAttack() const { return m_dpattack; }
    int getGold() const { return m_gold; }

    void reduceHealth(int dmg) { m_health -= dmg; }
    bool isDead() { return m_health <= 0; }
    void addGold(int amt) { m_gold += amt; }
};

class Player : public Creature
{
    int m_level{ 1 };

public:
    Player(std::string_view name)
        : Creature(name, '@', 10, 1, 0)
    {}
    void levelUp() { ++m_level; ++m_dpattack; }
    int getLevel() const { return m_level; }
    bool hasWon() const  { return m_level >= 20; }
};

class Monster : public Creature
{
public:
    enum class Type { dragon, orc, slime, max_types };
private:
    static const Creature& getDefaultCreature(Type type)
    {
        static const std::array<Creature, static_cast<size_t>(Type::max_types)> monsterData{
            { { "dragon", 'D', 20, 4, 100 },
              { "orc", 'o', 4, 2, 25 },
              { "slime", 's', 1, 1, 10 } }
        };
        return monsterData.at(static_cast<size_t>(type));
    }

public:
    Monster(Type t) : Creature{ getDefaultCreature(t) } {}
};

int main()
{
	Creature o{ "orc", 'o', 4, 2, 10 };
	o.addGold(5);
	o.reduceHealth(1);
	std::cout << "The " << o.getName() << " has " << o.getHealth()
        << " health and is carrying " << o.getGold() << " gold.\n";

    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    
    Player p(name);

    std::cout << "Welcome, " << p.getName() << ".\n" << "You have " << p.getHealth()
        << " health and are carrying " << p.getGold() << " gold.\n";

   	Monster m{ Monster::Type::orc };
	std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";

	return 0;
}
