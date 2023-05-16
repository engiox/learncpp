#include <iostream>
#include <utility>
#include <stdexcept>

class MoveClass
{
    int* m_resource{};
public:
    MoveClass() = default;
    MoveClass(int resource) : m_resource{ new int{resource} } {}
};
