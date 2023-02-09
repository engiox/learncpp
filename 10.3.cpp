#include <cstdint>
#include <iostream>
#include <ostream>
#include <string_view>
//using namespace std::literals;

enum Color : std::uint8_t
{
    black,
    red,
    blue,
};

enum Pet : std::uint8_t
{
    cat,
    dog,
    pig,
    whale,
};

constexpr std::string_view getColor(Color &color)
{
    switch (color)
    {
        case black:
            return "black";//sv;
        case red:
            return "red";//sv;
        case blue:
            return "blue";//sv;
        default:
            return "???";//sv;
    }
}

std::ostream& operator<<(std::ostream& out, Color &color)
{
    switch (color) {
        case black:
            return out << "black";
        case blue:
            return out << "blue";
        case red:
            return out << "red";
        default:
            return out << "???";
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, Pet &pet)
{
    switch (pet) {
        case cat:
            return out << "cat";
        case dog:
            return out << "dog";
        case pig:
            return out << "pig";
        case whale:
            return out << "whale";
        default:
            return out << "???";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Pet &pet)
{
    int input{};
    in >> input;

    pet = static_cast<Pet>(input);
    return in;
}

int main()
{
    Color shirt{ blue };
    Color shoe{ 1 };
    shoe = static_cast<Color>(0);

    std::cout << "Your shirt is " << getColor(shirt) << '\n';
    std::cout << "shirt is " << shirt << '\n';
    std::cout << "shoe is " << shoe << '\n';

    int input{};
    std::cin >> input;
    Pet myPet{ static_cast<Pet>(input) };
    std::cout << "My pet is " << myPet << '\n';

    return 0;
}
