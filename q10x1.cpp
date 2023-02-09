#include <iostream>
#include <string>
#include <string_view>

struct Monster
{
    enum class monsterType : std::uint8_t
    {
        ogre,
        dragon,
        orc,
        giant_spider,
        slime,
    };

    monsterType mtype {}; 
    std::string_view name {};
    int health {};
};

void printMoster(const Monster &monster)
{
    std::cout << "This ";

    switch (monster.mtype) {
        case Monster::monsterType::ogre:
            std::cout << "Ogre";
            break;
        case Monster::monsterType::dragon:
            std::cout << "Dragon";
            break;
        case Monster::monsterType::orc:
            std::cout << "Orc";
            break;
        case Monster::monsterType::giant_spider:
            std::cout << "Giant Spider";
            break;
        case Monster::monsterType::slime:
            std::cout << "Slime";
            break;
        default:
            std::cout << "???";
            break;
    }

    std::cout << " is named " << monster.name << " and has "
              << monster.health << " health.\n";
}

int main()
{
    Monster ogre { Monster::monsterType::ogre, "Torg", 145 }; 
    Monster slime { Monster::monsterType::slime, "Blurp", 23 };

    printMoster(ogre);
    printMoster(slime);

    return 0;
}
