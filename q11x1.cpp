#include <array>
#include <iostream>
#include <numeric>

enum ItemTypes
{
    item_healing_potion,
    item_torch,
    item_arrow,
    maxItem,
};

using Inventory = std::array<int, ItemTypes::maxItem>;

int countTotalItems(const Inventory &items)
{
    return std::reduce(items.begin(), items.end());
}

int main()
{
    Inventory items{ 2, 5, 10 };
    std::cout << "The player has " << countTotalItems(items) << " item(s) in total.\n";
    std::cout << "The player has " << items[item_torch] << " torch(es).\n";

    return 0;
}
