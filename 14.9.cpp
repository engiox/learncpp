#include <iostream>
#include <cassert>

class IntList
{
private:
    int m_list[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // give this class some initial state for this example

public:
    int& operator[] (int index);
    int operator[] (int index) const; // could also return const int& if returning a non-fundamental type
};

int& IntList::operator[] (int index) // for non-const objects: can be used for assignment
{
    assert(index >= 0 && index < static_cast<int>(std::size(m_list)));

    return m_list[index];
}

int IntList::operator[] (int index) const // for const objects: can only be used for access
{
    return m_list[index];
}

int main()
{
    IntList list{};
    list[2] = 3; // okay: calls non-const version of operator[]
    std::cout << list[2] << '\n';

    const IntList clist{};
//    clist[2] = 3; // compile error: calls const version of operator[], which returns by value.  Cannot assign to this because it is an rvalue.
    std::cout << clist[2] << '\n';

    IntList* plist{ new IntList{} };
    plist[2] = 3;
    delete plist;

    return 0;
}
