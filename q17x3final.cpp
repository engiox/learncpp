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

//    static Monster getRandomMonster()
//    {
//        int num{ Random::get(0, static_cast<int>(Type::max_types) - 1) };
//        return Monster{ static_cast<Type>(num) };
//    }
  
};

bool fightMonster(Player&, Monster&);
void attackMonster(Player&,  Monster&);
void attackPlayer(Player&, const Monster&);

int main()
{
    std::cout << "Enter your name: ";
    std::string playerName;
    std::cin >> playerName;
    std::cout << "Welcome, " << playerName << '\n';

    Player gPlayer{ playerName };
    Monster rMonster{ Monster::getRandomMonster() };

    while (true) {
//        Monster rMonster{ static_cast<Monster::Type>( Random::get(0,
//                    static_cast<int>(Monster::Type::max_types) ) ) };
        std::cout << "You have encountered a " << rMonster.getName()
                  << " (" << rMonster.getSymbol() << ").\n";

        if (!fightMonster(gPlayer, rMonster)) {
            rMonster = Monster::getRandomMonster();
            continue;
        }


        if (gPlayer.getHealth() <= 0) {
            std::cout << "You died at level " << gPlayer.getLevel()
                      << " and with " << gPlayer.getGold() << " gold.\n"
                      << "Too bad you can't take it with you!\n";
            break;
        }

        if (rMonster.isDead()) {
            gPlayer.levelUp();
            std::cout << "You killed the " << rMonster.getName() << ".\n"
                      << "You are now level " << gPlayer.getLevel() << ".\n";
            gPlayer.addGold(rMonster.getGold());
            std::cout << "You found " << rMonster.getGold() << ".\n";
            rMonster = Monster::getRandomMonster();
            if (gPlayer.getLevel() >= 20)
                break;
        }
    }

	return 0;
}

bool fightMonster(Player& player, Monster& monster)
{
    while (true) {
        std::cout << "Player: " << player.getHealth() << '/' << player.getDPAttack() << '\n';
        std::cout << "Monster: " << monster.getHealth() << '/' << monster.getDPAttack() << '\n';
        std::cout << "(R)un or (F)ight: ";
        char choice;
        std::cin >> choice;
        if ( choice == 'r' || choice == 'R' ) {
            if (Random::get(0, 1)) {
                std::cout << "You successfully fled.\n";
                return false;
            } else {
                std::cout << "You failed to flee.\n";
                attackPlayer(player, monster);
                continue;
            }
        }
        if ( choice == 'f' || choice == 'F') {
            attackMonster(player, monster);
            if (monster.getHealth() > 0)
                attackPlayer(player, monster);
        }
        if ( player.getHealth() <= 0 || monster.getHealth() <= 0)
            return true;
    }
}

void attackPlayer(Player& player, const Monster& monster)
{
    std::cout << "The " << monster.getName() << " hit you for "
              << monster.getDPAttack() << " damage.\n";
    player.reduceHealth(monster.getDPAttack());
}

void attackMonster(Player& player, Monster& monster)
{
    std::cout << "You hit the " << monster.getName() << " for "
              << player.getDPAttack() << " damage.\n";
    monster.reduceHealth(player.getDPAttack());
}
