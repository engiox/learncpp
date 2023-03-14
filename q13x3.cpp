#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include "Random.h"

class Monster
{
public:
    enum Type {
        Dragon, Goblin, Ogre, Orc,
        Skeleton, Troll, Vampire, Zombie,
        max_monster_types
    };

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hitPoint{};
public:
    Monster(Monster::Type type, std::string name, std::string roar, int hitPoint)
        : m_type{type}, m_name{name}, m_roar{roar}, m_hitPoint{hitPoint} {}

    void print()
    {
        std::cout << m_name << " the " << getTypeName() << " has "
                  << m_hitPoint << " hit points and says " << m_roar << '\n';
    }

    std::string_view getTypeName()
    {
        switch(m_type) {
            case Dragon:    return "dragon";
            case Goblin:    return "goblin";
            case Ogre:      return "ogre";
            case Orc:       return "orc";
            case Skeleton:  return "skeleton";
            case Troll:     return "troll";
            case Vampire:   return "vampire";
            case Zombie:    return "zombie";
            default:        return "???";
        }
    }
};

namespace MonsterGenerator
{
    Monster generateMonster()
    {
        Monster::Type type{static_cast<Monster::Type>(Random::get(0, Monster::max_monster_types))};
        int hp{Random::get(1, 100)};
        static constexpr std::array s_name{"Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans"};
        static constexpr std::array s_roar{"*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*"};
        auto name{s_name[Random::get(0, static_cast<int>(s_name.size()-1))]};
        auto roar{s_roar[Random::get(0, static_cast<int>(s_roar.size()-1))]};
        return Monster{type, name, roar, hp};
    }
}

int main()
{
	Monster skeleton{ Monster::Type::Skeleton, "Bones", "*rattle*", 4 };
	skeleton.print();

    Monster m{MonsterGenerator::generateMonster()};
    m.print();

    return 0;
}
