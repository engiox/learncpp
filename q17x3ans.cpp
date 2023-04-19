#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <sstream>
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
    bool isDead() const { return m_health <= 0; }
    void addGold(int amt) { m_gold += amt; }
};

class Potion
{
public:
    enum PotionType{ health, strength, Poison, max_types };
    enum PotionSize{ small, medium, large, max_sizes };

private:
    PotionType m_type{};
    PotionSize m_size{};

public:
    Potion(PotionType t, PotionSize s) : m_type{ t }, m_size{ s } {}
    PotionType getType() const { return m_type; }
    PotionSize getSize() const { return m_size; }

    static std::string_view getPotionTypeName(PotionType type)
    {
        static constexpr std::array names{ "Health", "Strength", "Poison" };
        return names.at(type);
    }

    static std::string_view getPotionSizeName(PotionSize size)
    {
        static constexpr std::array sizes{ "Small", "Medium", "Large" };
        return sizes.at(size);
    }

    std::string getPotionName() const
    {
        std::stringstream buff{};
        buff << getPotionSizeName(m_size) << " potion of " << getPotionTypeName(m_type);
        return buff.str();
    }

    static Potion getRandomPotion()
    {
        return {
            static_cast<PotionType>(Random::get(0, max_types - 1)),
            static_cast<PotionSize>(Random::get(0, max_sizes - 1))
        };
    }
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
    void drinkPotion(const Potion& pt)
    {
        std::cout << "You drank a " << pt.getPotionName() << '\n';
        switch (pt.getType()) {
            case Potion::health:
                switch (pt.getSize()) {
                    case Potion::small:
                        [[fallthrough]];
                    case Potion::medium:
                        m_health += 2;
                        break;
                    case Potion::large:
                        m_health += 5;
                        break;
                    case Potion::max_sizes:
                        break;
                }
                [[fallthrough]];
            case Potion::strength:
                ++m_dpattack;
                break;
            case Potion::Poison:
                --m_health;
                break;
            case Potion::max_types:
                break;
        }
    }
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
    if (player.isDead())
        return;
    monster.reduceHealth(player.getDPAttack());
    std::cout << "You hit the " << monster.getName()
              << " for " << player.getDPAttack() << " damage.\n";

    if (monster.isDead()) {
        std::cout << "You killed " << monster.getName() << '\n';
        player.levelUp();
        player.addGold(monster.getGold());
        std::cout << "You are now level " << player.getLevel() << '\n'
                  << "You found " << monster.getGold() << " gold.\n";
        if (Random::get(0, 9) < 3) {
            Potion pos{ Potion::getRandomPotion() };
            std::cout << "You found a mythical potion! Do you want to drink it? [y/n]: ";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                player.drinkPotion(pos);
            }
        }
    }
}

void attackPlayer(Player& player, const Monster& monster)
{
    if (monster.isDead() )
        return;
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

        if (choice == 'r' || choice == 'R') {
            if (Random::get(0, 1)) {
                std::cout << "You successfully fled.\n";
                return;
            } else {
                std::cout << "You failed to flee.\n";
                attackPlayer(player, rMonster);
//                if (player.isDead())
//                    return;
                continue;
            }
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

    while (!gPlayer.isDead() && !gPlayer.hasWon()) {
        fightMonster(gPlayer);
    }
    if (gPlayer.isDead()) {
        std::cout << "You died at level " << gPlayer.getLevel()
                  << " with " << gPlayer.getGold() << " gold.\n";
        std::cout << "Too bad you can't take it with you!\n";
    }
    if (gPlayer.hasWon()) {
        std::cout << "You have won with " << gPlayer.getGold()
                  << " gold at level " << gPlayer.getLevel() << "!\n";
    }

	return 0;
}
