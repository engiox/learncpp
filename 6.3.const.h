#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

namespace constants
{
    extern const double pi;
    extern const double avogadro;
    extern const double myGravity;

    // or

    inline constexpr double pi{ 3.14 };
    inline constexpr double avogadro{ 6.022143e23 };
    inline constexpr double myGravity{ 9.2 };
}

#endif
