#include <iostream>
#include <typeinfo>

namespace color {
    enum Color {
        red,
        green,
        blue,
        white
    };
}

enum Feeling {
    happy,
    tired,
//    blue,
};

enum {      // unnamed enumerations should be avoided
    one,
    two,
    three,
};

int main()
{
    color::Color apple{ color::red };
    color::Color shirt{ color::green };
    color::Color board{ color::blue };
    std::cout << apple << ", " << shirt << ", " << board << '\n';

    color::Color socks{ color::Color::white };
//    Color hat{ 2 };
    std::cout << socks << '\n';

    std::cout << one << ", " << two << ", " << three << '\n';
    std::cout << "type name of (red) is : " << typeid(color::red).name() << '\n';

    return 0;
}
