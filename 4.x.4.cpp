#include <iostream>

double getHeight();
void printFallDistance(double h, double t);

int main()
{
    double height {getHeight()};

    printFallDistance(height, 0);
    printFallDistance(height, 1);
    printFallDistance(height, 2);
    printFallDistance(height, 3);
    printFallDistance(height, 4);
    printFallDistance(height, 5);

    return 0;
}

double getHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    double height{};
    std::cin >> height;
    return height;
}

void printFallDistance(double h, double time)
{
    constexpr double gravity_constant{ 9.8 };
    double height{h};

    height = h - gravity_constant * time * time / 2;
    
    if (height <= 0)
        std::cout << "At " << time << "seconds, the  ball is on the ground.\n";
    else
        std::cout << "At " << time << " seconds, the ball is at height: "
            << height << " meters\n";
}
