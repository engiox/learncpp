#include <iostream>

namespace animal
{
    enum Animal
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        maxNumberOfAnimals
    };
}


int main()
{
    double hiTemp[365] {};
    hiTemp[0] = -2.2;

    int legsOfAnimal[animal::maxNumberOfAnimals] { 2, 4, 4, 4, 2, 0, };

    std::cout << "Elephant has " << legsOfAnimal[animal::elephant] << " legs.\n";

    return 0;
}
