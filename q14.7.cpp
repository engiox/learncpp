#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include "Fraction.h"
#include "Car.h"

int main()
{
	Fraction f1{ 3, 2 };
	Fraction f2{ 5, 8 };

	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
	std::cout << f1 << ((f1 < f2) ? " < " : " not < ") << f2 << '\n';
	std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';

    std::vector<Car> cars{
        {"Toyota", "Corolla"},
        {"Honda", "Accord"},
        {"Toyota", "Camry"},
        {"Honda", "Civic"}
    };

    std::sort(cars.begin(), cars.end()); // requires an overloaded operator<

    for (const auto &car : cars)
        std::cout << car << '\n'; // requires an overloaded operator<<

    return 0;
}
