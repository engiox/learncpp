#include <iostream>
#include <typeinfo>
#include <iomanip>

int main()
{
    int array[]{ 9, 7, 5, 3, 1 };
    std::cout << "array  : " << std::setw(6) << typeid(array).name() << " : " << array << '\n';
    std::cout << "&array : " << std::setw(6) << typeid(&array).name() << " : " << &array << '\n';

    int *ptr{ array };
    std::cout << "ptr    : " << std::setw(6) << typeid(ptr).name() << " : " << ptr << '\n';
    std::cout << "&ptr   : " << std::setw(6) << typeid(&ptr).name() << " : " << &ptr << '\n';

    return 0;
}
