#include <ios>
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>

int getNameCount()
{
    int numNames{};

    do {
        std::cout << "How many names would you like to enter? ";
        std::cin >> numNames;
//        if (std::cin.fail()) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            continue;
//        }
    } while (numNames < 0);

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return numNames;
}

void getNames(std::string *pNames, int num)
{
    for (int index{0}; index < num; ++index) {
        std::cout << "Enter name #" << index << ": ";
        std::getline(std::cin, pNames[index], '\n');    // getline(std::cin >> std::ws, pStr);
    }
}

void printNames(std::string *pNames, int num)
{
    std::cout << "Here is your sorted list:\n";

    for (int index{0}; index < num; ++index) {
        std::cout << "Name #" << index << ": "
                  << pNames[index] << '\n';
    }
}

int main()
{
    int num{getNameCount()};

    std::string *pNames{ new std::string[(size_t)num]{} };

    getNames(pNames, num);

    std::sort(pNames, pNames+num);

    printNames(pNames, num);

    delete[] pNames;

    return 0;
}
