#include <cassert>
#include "Array.h"

template <typename T>
Array<T>::Array(int len) : m_length{ len }
{
    assert(m_length > 0 && "Zero length array\n");
    m_data = new T[m_length]{};
}

template <typename T>
Array<T>::~Array()
{
    delete[] m_data;
}

template <typename T>
void Array<T>::erase()
{
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
}

template <typename T>
T& Array<T>::operator[](const int index) const
{
    assert(index >= 0 && index < m_length && "Index out of range\n");
    return m_data[index];
}

template <typename T>
int Array<T>::getLength() const
{
    return m_length;
}

template class Array<int>;
template class Array<double>;
