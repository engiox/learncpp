#include <iostream>
#include <cstring>

template <typename T, int size>
class StaticArray
{
    T m_array[size]{};
public:
    T* getArray() { return m_array; }
    T& operator[](int index) { return m_array[index]; }
    void print() {
        for (int i{0}; i < size; ++i) {
            std::cout << m_array[i] << ' ';
        }
        std::cout << '\n';
    }
};

template <typename T, int size>
void print(StaticArray<T, size>& array)
{
    for (int count{0}; count < size; ++count)
        std::cout << array[count] << ' ';
}

template <int size>
void print(StaticArray<char, size>& array)
{
    for (int count{0}; count < size; ++count)
        std::cout << array[count];
}

void p1()
{
	// declare an int array
	StaticArray<int, 4> int4{};
	int4[0] = 0;
	int4[1] = 1;
	int4[2] = 2;
	int4[3] = 3;

	// Print the array
	print(int4);
}

void p2()
{
    // declare a char array
    StaticArray<char, 14> char14{};

    std::strcpy(char14.getArray(), "Hello, world!");

    // Print the array
    print(char14);
}

void p3()
{
    StaticArray<char, 12> char12{};

	std::strcpy(char12.getArray(), "Hello, mom!");

	// Print the array
	print(char12);
}

int main()
{
    p1();
    std::cout << '\n';

    p2();
    std::cout << '\n';

    p3();
    std::cout << '\n';

	return 0;
}
