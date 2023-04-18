#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include "Random.h"

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

    static Type getRandomMonster()
    {
        return static_cast<Type>(Random::get(0, static_cast<int>(Type::max_types) - 1));
    }
};

void attackMonster(Player& player, Monster& monster)
{
    monster.reduceHealth(player.getDPAttack());
    std::cout << "You hit the " << monster.getName()
              << " for " << player.getDPAttack() << " damage.\n";

    if (monster.isDead()) {
        std::cout << "You killed " << monster.getName() << '\n';
        player.levelUp();
        player.addGold(monster.getGold());
        std::cout << "You are now level " << player.getLevel() << '\n'
                  << "You found " << monster.getGold() << " gold.\n";
    }
}

void attackPlayer(Player& player, const Monster& monster)
{
    player.reduceHealth(monster.getDPAttack());
    std::cout << "The " << monster.getName() << " hit you for "
              << monster.getDPAttack() << " damage.\n";
    
//    if (player.isDead()) {
//        std::cout << "You died at level " << player.getLevel()
//                  << " and with " << player.getGold() << " gold.\n";
//        std::cout << "Too bad you can't take it with you!\n";
//    }
}

void fightMonster(Player& player)
{
    Monster rMonster{ Monster::getRandomMonster() };
    std::cout << "You have encountered a " << rMonster.getName()
              << " (" << rMonster.getSymbol() << ")\n";

    while (!player.isDead() && !rMonster.isDead()) {
        std::cout << "(R)un or (F)ight: ";
        char choice;
        std::cin >> choice;

        if ((choice == 'r' || choice == 'R') && Random::get(0, 1)) {
            std::cout << "You successfully fled.\n";
            return;
        } else {
            std::cout << "You failed to flee.\n";
            attackPlayer(player, rMonster);
            if (player.isDead())
                return;
            continue;
        }

        if (choice == 'f' || choice == 'F') {
            attackMonster(player, rMonster);
            attackPlayer(player, rMonster);
        }
    }
}

int main()
{
    std::cout << "Enter your name: ";
    std::string playerName;
    std::cin >> playerName;
    std::cout << "Welcome, " << playerName << '\n';

    Player gPlayer{ playerName };

    while (true) {
        fightMonster(gPlayer);
        if (gPlayer.isDead()) {
            std::cout << "You died at level " << gPlayer.getLevel()
                      << " with " << gPlayer.getGold() << " gold.\n";
            std::cout << "Too bad you can't take it with you!\n";
            break;
        }
        if (gPlayer.hasWon()) {
            std::cout << "You have won with " << gPlayer.getGold()
                      << " gold at level " << gPlayer.getLevel() << "!\n";
            break;
        }
    }

	return 0;
}
