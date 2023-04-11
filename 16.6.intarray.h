#ifndef _INTARRAY_H_
#define _INTARRAY_H_

#include <cassert>
#include <initializer_list>

class IntArray
{
    int m_length{ 0 };
    int* m_data{ nullptr };
    void allocate(int allocSize);
    void copyFrom(const IntArray& src, int iBegin, int iEnd);

public:
    IntArray() = default;
    IntArray(int size);
    IntArray(std::initializer_list<int> list);
    ~IntArray();
    void erase();
    int& operator[](int index);
    int& operator[](int index) const;
    int getLength() const;
    void reallocate(int newSize);   // destroy existing elements
    void resize(int newSize);       // keep existing elements
    IntArray(const IntArray& src);
    IntArray& operator=(const IntArray& src);   // self-assignment check !!!
    void insertBefore(int value, int index);
    void remove(int index);
    void insertAtBeginning(int value);
    void insertAtEnd(int value);
};

#endif
