#include <iostream>
#include <utility>

template <typename T, typename U>
struct Pair
{
    T first {};
    U second {};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    std::pair<int, int> p1 { 1, 2 };
    std::pair p2 {3, 4.5};

    Pair<double, int> p3 {6.7, 8};
    Pair p4 {9, 0.0};
    Pair p5 {1, 2};

    return 0;
}
