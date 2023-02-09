#include <iostream>
#include <string_view>

enum class MonsterType
{
    ogre,
    dragon,
    orc,
    giant_spider,
    slime,
};

struct Monster
{
    MonsterType monsterType {};
    std::string_view name {};
    int health {};
};

const std::string_view getMonsterTypeString(MonsterType mtype)
{
    switch (mtype) {
        case MonsterType::ogre:
            return "Ogre";
        case MonsterType::dragon:
            return "Dragon";
        case MonsterType::orc:
            return "Orc";
        case MonsterType::giant_spider:
            return "Giant Spider";
        case MonsterType::slime:
            return "Slime";
        default:
            return "???";
    }
}

void printMonster(const Monster &monster)
{
    std::cout << "This " << getMonsterTypeString(monster.monsterType) << " is named "
              << monster.name << " and has " << monster.health << "health.\n";
}

int main()
{
    Monster mon1 { MonsterType::ogre, "Torg", 145 };
    Monster mon2 { MonsterType::slime, "Blurp", 23 };

    printMonster(mon1);
    printMonster(mon2);
    
    return 0;
}
