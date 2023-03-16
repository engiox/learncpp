#ifndef _CAR_H_
#define _CAR_H_

#include <iostream>
#include <string>

class Car
{
    std::string m_make{};
    std::string m_model{};
public:
    Car(std::string make, std::string model);

    friend std::ostream &operator<<(std::ostream &out, const Car &car);
    friend bool operator==(const Car &car1, const Car &car2);
    friend bool operator!=(const Car &car1, const Car &car2);
    friend bool operator<(const Car &car1, const Car &car2);
};

#endif
