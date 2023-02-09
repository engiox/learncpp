// Donald Knuth
// "The Art of Computer Programming, Volume II : Seminumerical Algorithms"
// Addison-Wesley, 1969
// Modified version to handle small numbers

#include <algorithm>
#include <cmath>

// return true if the difference between a and b is within epsilon percent
// of the larger a and b

// RECOMMENDED VALUES FOR absEpsilon and relEpsilon
// absEpsilon = 1e-12, relEpsilon = 1e-8
//
inline bool isEqualRel(double a, double b,
        double absEpsilon = 1e-12, double relEpsilon = 1e-8)
{
    // Check if the numbers are really close -- needed when comparing numbers near zero.
    double diff{std::abs(a-b)};
    if (diff <= absEpsilon)
        return true;

    // Otherwise fall back to Knuth's algorithm
    return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
