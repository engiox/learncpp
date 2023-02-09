#include <iostream>

template <typename T>
struct Triad
{
    T m1 {};
    T m2 {};
    T m3 {};
};

template <typename T>
void print(const T &tri)
{
    std::cout << "[" << tri.m1 << ", " << tri.m2
              << ", " << tri.m3 << "]";
}

//template <typename T>
//Triad(T, T, T) -> Triad<T>;

int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}
