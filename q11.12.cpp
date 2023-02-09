#include <iostream>
#include <string>
#include <limits>

int main()
{
    std::cout << "How many names would you like to enter? ";
    std::size_t num{};
    std::cin >> num;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    auto *pNames{ new std::string[num]{} };

    for (size_t i{ 0 }; i < num; ++i) {
        std::cout << "Enter name #" << i+1 << ": ";
        std::getline(std::cin, pNames[i]);
    }

    std::cout << pNames << " : " << pNames+num << '\n';

    std::sort(pNames, pNames+num);

    std::cout << "Here is your sorted list:\n";
    for (size_t i{0}; i < num; ++i) {
        std::cout << "Name #" << i + 1 << ": " << pNames[i]
                  << " @ " << pNames+i << '\n';
    }
    
    return 0;
}
