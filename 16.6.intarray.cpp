#include <iostream>
#include <initializer_list>
#include <cassert>
#include "IntArray.h"

IntArray::IntArray(int size) : m_length{ size }
{
    assert(size >= 0 && "Negative size not allowed\n");
    if (size > 0) {
        allocate(size);
    }
    assert(m_data != nullptr && "Allocation failed\n");
}

//IntArray::IntArray(const IntArray& src) : m_length{ src.m_length }
//{
//    allocate(m_length);
//    copyFrom(src, 0, m_length);
//}

IntArray::IntArray(const IntArray& src) : IntArray(src.m_length)
{
    copyFrom(src, 0, m_length);
}

IntArray::IntArray(std::initializer_list<int> list) : IntArray(static_cast<int>(list.size()))
{
    int count{0};
    for (int element : list) {
        m_data[count] = element;
        ++count;
    }
}

IntArray::~IntArray()
{
    delete[] m_data;
}

void IntArray::allocate(int allocSize)
{
    assert(allocSize >= 0 && "Negative allocation size\n");
    if (allocSize > 0) {
        m_length = allocSize;
        m_data = new int[static_cast<size_t>(m_length)];
    }
}

void IntArray::copyFrom(const IntArray& src, int iBegin, int iEnd)
{
    assert(m_length >= src.m_length && "Source is bigger than target\n");
    assert(iBegin >= 0 && "Negative index not allowed\n");
    assert(iEnd <= m_length && "Index out of range\n");
    for (int i{iBegin}; i < iEnd; ++i) {
        m_data[i] = src.m_data[i];
    }
}

void IntArray::erase()
{
    delete[] m_data;
    m_data = nullptr;
    m_length = 0;
}

int& IntArray::operator[](int index)
{
    assert( index >= 0 && index < m_length && "Index out of range\n");
    return m_data[index];
}

int& IntArray::operator[](int index) const
{
    assert( index >= 0 && index < m_length && "Index out of range\n");
    return m_data[index];
}

int IntArray::getLength() const
{
    return m_length;
}

void IntArray::reallocate(int newSize)   // destroy existing elements
{
    erase();
    allocate(newSize);
}
                                        
void IntArray::resize(int newSize)       // keep existing elements
{
    if (newSize == m_length) return;
    if (newSize <= 0) {
        erase();
        return;
    }

    int* newData{ new int[static_cast<size_t>(newSize)]{} };

    for (int i{0}; i < ((newSize < m_length) ? newSize : m_length); ++i) {
        newData[i] = m_data[i];
    }
    erase();
    m_data = newData;
    m_length = newSize;
}

IntArray& IntArray::operator=(const IntArray& src)   // self-assignment check !!!
{
    if (&src == this) return *this;

    reallocate(src.m_length);
    copyFrom(src, 0, m_length);
    return *this;
}

void IntArray::insertBefore(int value, int index)
{
    assert(index >= 0 && index < m_length && "Index out of range\n");
    resize(m_length + 1);
    for (int i{m_length}; i >= index; --i) {
        m_data[i] = m_data[i - 1];
    }
    m_data[index] = value;
}

void IntArray::remove(int index)
{
    assert(index >= 0 && index < m_length && "Index out of range\n");
    for (int i{index}; i < m_length - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    resize(m_length - 1);
}

void IntArray::insertAtBeginning(int value)
{
    insertBefore(value, 0);
}

void IntArray::insertAtEnd(int value)
{
    insertBefore(value, m_length);
}
