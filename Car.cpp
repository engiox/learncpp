#include "Car.h"

Car::Car(std::string make, std::string model)
    : m_make{make}, m_model{model}
{
}

std::ostream &operator<<(std::ostream &out, const Car &car)
{
    out << '(' << car.m_make << ", " << car.m_model << ')';
    return out;
}

bool operator==(const Car &car1, const Car &car2)
{
    return (car1.m_make == car2.m_make) && (car1.m_model == car2.m_model);
}

bool operator!=(const Car &car1, const Car &car2)
{
    return !(car1 == car2);
}

bool operator<(const Car &car1, const Car &car2)
{
    if (car1.m_make == car2.m_make)
        return car1.m_model < car2.m_model;
    else
        return car1.m_make < car2.m_make;
}
