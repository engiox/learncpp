#include <iostream>
#include <vector>

template <typename T>
void printLen(const std::vector<T> &v)
{
    std::cout << "The length is: " << v.size() << '\n';
}

int main()
{
    // Vectors remember their length
    {
        std::vector vi{ 9, 7, 5, 3, 1 };
        printLen(vi);

        vi = {3, 6, 9};
        printLen(vi);
    }

    // Resizing a vector
    {
        std::vector v{ 0, 1, 2 };
        v.resize(5);

        for (auto elem : v) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }

    // Initializing a vector to a specific size
    {
        std::vector v1{ 5, 6 };
        std::vector v2( 5, 6 );

        for (auto elem : v1)
            std::cout << elem << ' ';
        std::cout << '\n';

        for (auto elem : v2)
            std::cout << elem << ' ';
        std::cout << '\n';
    }

    // Compacting bools
    {
        std::vector v1{ true, false, false, true, false, true };
        std::cout << "The length is: " << v1.size() << '\n';
        std::cout << "The sizeof() is: " << sizeof(v1) << '\n';
        for (auto i : v1)
            std::cout << i << ' ';
        std::cout << '\n';

        std::vector v2(8192, false);
        std::cout << "The length is: " << v2.size() << '\n';
        std::cout << "The sizeof() is: " << sizeof(v2) << '\n';
        for (size_t index{ 0 }; auto i : v2) {
            if (index % 2) i = true;
            std::cout << i;
            ++index;
        }
        std::cout << '\n';
    }

    return 0;
}
